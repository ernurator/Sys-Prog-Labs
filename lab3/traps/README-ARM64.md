# Apple Silicon (M1) / ARM64-specific instructions

**If you have an Intel machine**, please ignore the
instructions below.

**If you have an Apple Silicon (ARM64) machine**,
please follow the specific instructions we provide
in the project handout.

In essence, you want to use `gdb-multiarch -ix trap1.gdb`
and `gdb-multiarch -ix trap2.gdb` to run GDB on your
traps. Inside GDB, you want to use the `rt` (run trap)
command instead of the normal `r` (run) command.
