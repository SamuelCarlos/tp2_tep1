# :hamster: TP2 - CPokémon :tiger:

> [Bruno Carneiro Izoton](https://github.com/brunoizoton2001)

> [Samuel Carlos Xavier de Carvalho](https://github.com/SamuelCarlos)

## :rocket: What is CPokemon?

CPokemon is a coursework to Tópicos Especiais em Programação class.
The objective is the implementation of Dispatch Tables and Dynamic Chained List.

## :hammer: How it works?

Basically we have Dispatch Tables to hold all the pokémon attacks and to hold the attacks debuffs.

We used the "debuff" logic to apply effects like sleep, burn, and paralyzed to the pokémons.
Everytime a pokémon uses a skill that applies a debuff, we call the attack dispatch and inside the attack function calls the debuff dispatch and add the debuff in a "debuff list" to the respective pokémon that is taking damage, after this, we turn to true (1) the condition in the conditions array.

Every debuff have a countdown and every turn we count -1 to the total turns remaining. When it comes to 0, we remove this debuff and its respective condition from the pokémon.

All damage is calculated as required.

## :1234: Menus

### :video_game: 1 - Jogar

Choose your name and your pokemons and go to the fight.

### :bar_chart: 2 - Melhores pontuações

Displays the scores of all players in an orderly manner on the screen.

### :door: 3 - Sair

Exit the application.

## :recycle: Obs

:file_folder: **Files:** To make it easier to save pokemons and attacks in the lists created in the program, we made use of files. In the file "pokemons.csv" we list all pokemons available for use and their respective attacks. In the file "attacks.csv" we list all available attacks.

:evergreen_tree: **Trees:** We've used trees while reading the file to save the score ordenated. We have a score based tree, and inside each ramification, we have another tree. In case of 2 players have the same score the secondary tree is used to organize the names in order.
We used recursive functions to walk in the tree.

:clipboard: **Lists:** We used chained lists to hold on every data like player pokemons and it's debuffs.

:bomb: **Troubles:** We had some troubles with debuffs aplication, that resulted in many variable uses and many conditionals at Battle.c, where the turns are counted and the battle occurs.
