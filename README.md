# Linux Beeps

Collection of `beep` scripts to play music from pc speaker.

Where possible, the source is documented as a comment in each individual file.

## No PC speaker?

Most modern machines have no `pcspkr` for the real `beep` to drive. The included
[`beep`](beep) is a drop-in replacement that parses the same flags and plays the
tones through your sound card instead (PipeWire / ALSA / PulseAudio / sox /
ffmpeg). Needs python3 and one of `pw-cat`, `aplay`, `play`, `ffplay`, `paplay`.

Put it ahead of the real `beep` in `PATH` and the scripts play unmodified:

```sh
# one-off
PATH="$PWD:$PATH" bash mario-victory.sh

# or symlink it somewhere early in PATH
ln -s "$PWD/beep" ~/.local/bin/beep
```

Defaults to a square wave to match the 1-bit pc-speaker buzz. Tweak via env vars:

| Variable       | Default  | Meaning                                      |
| -------------- | -------- | -------------------------------------------- |
| `BEEP_WAVE`    | `square` | `square`, `sine`, or `triangle`              |
| `BEEP_VOLUME`  | `50`     | output level, `0` - `100`                    |
| `BEEP_FADE_MS` | `2`      | anti-click fade per tone edge (`0` = rawest) |
| `BEEP_RATE`    | `44100`  | sample rate                                  |
| `BEEP_PLAYER`  | auto     | force a known player by name                 |
| `BEEP_COMMAND` | auto     | full custom command reading a WAV on stdin   |
