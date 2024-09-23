# Conway's Game of Life

Matrix greenrain screensavers are getting old!

This is a fairly simple implementation of Conway's celular automaton *The Game of Life*, directly available from the terminal. Now there is a tiny living world in your workspace :3

Right now the only initial configuration is *The R-pentomino* (this one):

```
 #
##
 ##
```

## Usage

Execute:

```sh
conway
```

Options:

| flag      | description                              | default |
|-----------|------------------------------------------|---------|
|`-c [char]`| The character representing a living cell | #       |
|`-d [int]` | The delay time between ticks             | 50      |
|`-h`       | Show help                                |         |

Other example:

```sh
conway -c 8 -d 25
```

## Install

```sh
curl -Ls https://raw.githubusercontent.com/ivaaane/conway/refs/heads/main/install.sh | bash
```

## Roadmap

- [x] Thing works.

- [ ] More default configurations.

- [ ] Option to input custom configuration.

- [ ] Option to limit the number of generations.

- [ ] Option to randomize the initial configuration.

- [ ] Color options.
