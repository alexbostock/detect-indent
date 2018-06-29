# detect-indent

A simple program to guess the indentation style used in a given file (assumed to be source code). This is language agnostic; it will not parse the file.

Output is an integer number of spaces, or 0 to indicate indentation with tabs. In case of failure or uncertainty, it will output either 4 or 2, as a reasonable guess.

To compile:

```
gcc -o ~/bin/detect-indent detect-indent.c
```

To use indent detection when a file is opened in [Kakoune](https://github.com/mawww/kakoune), add this to `~/.config/kak/kakrc`:

```
hook global BufOpenFile .* %{
	set-option buffer indentwidth %sh{ detect-indent "$kak_hook_param" }
}
```
