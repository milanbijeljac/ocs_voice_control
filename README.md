# ocs_voice_control

A desktop voice assistant for Windows, written in C++. It listens on the microphone,
transcribes speech locally with Whisper.cpp, matches the text against a list of known
commands, and executes them (launching applications, sending keystrokes).

Everything runs offline — no audio leaves the machine.

> **Status: early development.** PortAudio initializes and enumerates input devices.
> Audio capture, speech recognition and command handling are not implemented yet.
> See [Roadmap](#roadmap) for what works and what does not.

---

## Architecture

The application is built in four layers:

| Layer | Responsibility | Component |
|-------|----------------|-----------|
| 1. Capture | microphone → PCM samples | `AudioCapture` → `AudioBuffer` |
| 2. Recognition | PCM → text | `SpeechEngine` (Whisper.cpp) |
| 3. Parsing | text → command | `CommandRegistry` |
| 4. Execution | command → action | `ActionExecutor` (Win32) |

Capture and recognition run on separate threads and communicate through a thread-safe
queue, since the PortAudio callback runs on its own audio thread and must never block:

```
Audio thread   →  PortAudio callback   ── writes ──┐
                                                   ▼
                                             AudioBuffer
                                                   ▲
Worker thread  →  Whisper transcription  ── reads ──┘
                                                   │
                                                   ▼
Main thread    →  command dispatch + Win32 message loop
```

Audio format is fixed at **16 kHz, mono, `float`** — the format Whisper expects, chosen
up front to avoid resampling later.

---

## Tech stack

- **Visual Studio 2022** — build environment (console subsystem during development)
- **vcpkg** (manifest mode) — dependency management
- **PortAudio** — microphone capture, callback API
- **Whisper.cpp** — local speech-to-text
- **Win32 API** — `ShellExecuteEx` for launching apps, `SendInput` for keystrokes
- **C++20** — `std::jthread`, `std::stop_token`

---

## Building

### 1. Install vcpkg and integrate it with Visual Studio

```
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

The last command needs an elevated shell.

### 2. Open and build

Open `ocs_voice_control.slnx` in Visual Studio and build.

Dependencies are declared in `vcpkg.json` and installed automatically on the first build
into `vcpkg_installed/` (gitignored) — no manual `vcpkg install` step is needed.

> **The configuration must be `x64`.** The vcpkg triplet is `x64-windows`; building as
> `Win32` produces linker errors.

### 3. Whisper model

Whisper models are not in the repository (~150 MB). Download `ggml-base.en.bin` from
[Hugging Face](https://huggingface.co/ggerganov/whisper.cpp/tree/main) and place it in
`models/`.

---

## Repository layout

```
ocs_voice_control/
├── src/
│   ├── main.cpp                  thin entry point: constructs App, calls run()
│   ├── app/
│   │   └── app.h/.cpp            owns components, drives the main loop
│   ├── audio/
│   │   ├── audio_capture.h/.cpp  PortAudio stream and callback
│   │   └── audio_buffer.h/.cpp   thread-safe queue (mutex + condition_variable)
│   ├── speech/                   Whisper.cpp wrapper (empty)
│   └── commands/                 command registry and action executor (empty)
├── models/                       Whisper models (not tracked)
├── config/                       user-defined commands (not implemented)
├── vcpkg.json                    dependency manifest
└── ocs_voice_control.slnx        Visual Studio solution
```

`main()` is deliberately kept minimal so that switching from a console app to a
background tray application later only touches `main()` and the linker subsystem setting.

---

## Roadmap

| Step | Goal | Status |
|------|------|--------|
| 0 | PortAudio init, enumerate input devices | done |
| 1 | Microphone → live level meter in console | in progress |
| 2 | Whisper transcript printed to console | not started |
| 3 | Command match → launch an application | not started |
| 4 | Tray icon, background operation | not started |
| 5 | Config file for user-defined commands | not started |

The console stays until step 3 works end to end — speak, see the transcript, watch the
command fire. It is the best debugging tool available for the first three steps.

---

## Design notes

- **`AudioBuffer` starts as `std::queue` + `mutex` + `condition_variable`.** Locking in a
  real-time audio callback is an anti-pattern, accepted here knowingly: a dropped chunk
  only degrades a transcript. A lock-free SPSC ring buffer is a later refinement.
- **Two queues, one pattern.** Audio flows capture → recognition, and text flows
  recognition → dispatch. Both are producer-consumer, which makes a generic
  `ThreadSafeQueue<T>` the natural end state.
- **Utterance segmentation is an open question.** Whisper is not a streaming recognizer;
  something has to decide when a sentence is finished. A fixed N-second window is the
  simple starting point, silence detection (VAD) the better one.
- **Command matching needs normalization first.** Whisper returns `"Open Notepad++."` —
  capitalization and punctuation included. Lowercasing and stripping punctuation comes
  before any matching, exact or fuzzy.
