# Get the directory where this script is located
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Create build directory if it doesn't exist
if [ ! -d "$SCRIPT_DIR/build" ]; then
    mkdir -p "$SCRIPT_DIR/build"
fi

# Check if makefile exists in the build directory
if [ ! -f "$SCRIPT_DIR/build/Makefile" ]; then
    # Run cmake if makefile is not found
    echo "Makefile not found. Running cmake .."
    if ! cmake -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/build"; then
        # Display an error message and exit if cmake fails
        echo -e "\e[31mcmake .. failed. Exiting.\e[0m"
        exit 1
    fi
fi

# Build in the coprocessor build directory
if make -C "$SCRIPT_DIR/build"; then
    echo -e "\e[32mBuild successful.\e[0m"
else
    # Display an error message and exit if the build fails
    echo -e "\e[31mBuild failed, exiting.\e[0m"
    exit 1
fi