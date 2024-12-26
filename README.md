# Card Game C++ Challenge

## Build

The project has been ported to CMake which will generate visual studio project files for Visual Studio and a MakeFile for Linux.

## Key Design Decisions for Game Class Library

### Namespace Encapsulation
The `cardgame` namespace isolates the game-related functionality, preventing potential naming conflicts and improving code organization for larger projects.

### Strong Typing with `enum class`
The `Player` enumeration uses `enum class` for:
- Scoped enumeration to prevent collisions with other enumerators.
- Strong typing for improved type safety and clarity.

### Constants for Game Rules
The constants `NUM_CARDS` and `NUM_CARDS_HALF`:
- Provide a single source of truth for card-related values.
- Utilize `constexpr` for compile-time evaluation, ensuring minimal runtime overhead.
- Include a `static_assert` to guarantee logical consistency (e.g., `NUM_CARDS` is even).

### Overloaded Constructors
The `Game` class offers two constructors:
1. Initializes the game with a shuffled deck. This ensures that each game starts with a random distribution of cards.
2. Allows initializing the game with a pre-shuffled deck, leveraging compile-time bounds checking. This is useful for testing and scenarios where a specific card distribution is required.

### Functional Callbacks
The `RoundCallback` type allows users to define custom behavior for each round without altering the game logic. This is achieved using `std::function`, enabling:
- Decoupling of game mechanics and external behavior.
- Support for various callable objects (e.g., lambdas, function pointers).

### Member Functions
#### Public API
- **`GetPlayer1Score` and `GetPlayer2Score`**: Provide direct access to player scores.
- **`Play`**: Encapsulates the entire game loop, invoking the callback for each round, and returns the overall winner. Marked with `[[nodiscard]]` to encourage handling the result.

#### Private Implementation Details
- **Encapsulation**: Private members and helper functions ensure internal state and logic are hidden from external users, reducing the risk of misuse and simplifying maintenance.
- **Separation of Concerns**: Helper methods (`GenerateDeck`, `Shuffle`, `Split`) modularize the logic for clarity and reuse.

### Efficient Storage and Operations
- **`std::vector`**: Used for player card storage due to its dynamic resizing and efficient iteration.
- **`std::array`**: Used in the pre-shuffled constructor for fixed-size deck representation, leveraging compile-time bounds checking.

### Shuffle Algorithm
The Fisher-Yates shuffle is used for its:
- Proven randomness properties.
- Linear time complexity (O(n)).

### Game Logic
The game logic is cleanly separated into distinct methods:
- **`PlayCurrentRound`**: Manages a single round, ensuring modularity.
- **`GetWinner`**: Determines the winner of the current state, enabling consistent evaluation.
- **`GetGameOver`**: Signals the end of the game, enhancing clarity.

## Code Quality and Modern Features
- **`[[nodiscard]]` Attribute**: Encourages the user to handle return values where critical.
- **Static Methods**: Encapsulate utility functions (`GenerateDeck`) that don't rely on instance-specific state.
- **Const-Correctness**: Ensures methods like `GetPlayer1Score` and `GetPlayer2Score` do not modify state, enabling safer usage.

## Conclusion
This header file demonstrates a robust, modern, and extensible design for a card game. The combination of clear abstractions, adherence to best practices, and efficient algorithms ensures high code quality and ease of use.
