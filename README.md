# Ship - SHell, Interactive and POSIX compliant

Ship is a 
- a friendly interactive shell 
- that's actually POSIX compliant for once.
- it also (tries to be at least) not ridiculously slow...

## Massive Disclaimer:

This shell is in an _extremely infant stages_ right now.

This project is sort of just me learning about writing interpreters. I'm trying
to make this something at least actually usuable as a daily shell, but it may
take a while seeing that I am a beginner to C and that I suck at programming in
general. I get that this is quite an ambitious project for someone who both 
sucks at programming and sucks at C, but y'know what, I'm already here, I 
started this and I plan on finishing it...

So, this project might take some time before it's actually usuable... a _long
time_ actually...

## Motivation

For some reason, a lot of "friendly" interactive shells aren't POSIX compliant?
Take example:
- Fish
- Elvish

I don't quite get it. I get that POSIX is not very fun in terms of usability, 
but I also think that forcing the user to
- learn a new, bizarre syntax that the user will literally never use again 
  anywhere outside of their interactive shell
- having to translate already existing snippets of valid shell script or 
  translating their current shell scripts to some bizarre syntax

is quite counterintuitive to the notion of a shell being "friendly". 

I know, I know, Zsh and Zsh plugins exist. While Zsh has some pretty good 
plugins, the reality is that Oh-My-Zsh is unbareably slow. Plus, their plugins
just don't quite hit the same spot as something like Fish either, so here I am
I guess, trying to program an interactive shell that's POSIX compliant for once
but it also has "friendly" interactive features, such as
- Fish-like autocomplete 
  - Fish-like manpage completions 
- Fish-like autosuggestions
- Fish-like syntax heighlighting (yeahhhh I'm quite the fan of Fish...)
- Zsh-like prompt configuration
  - git prompt support built in
- _some_ semblance of Bash compatibility

This might be a pipe dream though. I have quite the ways to go. As of right now
_I need to at least have a working POSIX shell first_, so this might take a
while...
