#!/bin/bash
# Build script for rebuilding all the Just Forge Engine projects
set echo on
mkdir -p build/

echo "Building everything..."

make -f Makefile.engine.linux.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building Just Forge Engine at errorlevel $ERRORLEVEL" && exit $ERRORLEVEL
fi
echo "Successfully built engine"

make -f Makefile.tester.linux.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building engine-tester at errorlevel $ERRORLEVEL" && exit $ERRORLEVEL
fi
echo "Successfully built engine-tester"

make -f Makefile.tests.linux.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building tests at errorlevel $ERRORLEVEL" && exit $ERRORLEVEL
fi
echo "Successfully built tests"

echo "Successfully built everything!"

echo "Which program would you like to run?"
options=("tests" "Just_Forge_Tester" "both")
select opt in "${options[@]}"
do
    case $opt in
        "tests")
            echo "Running all tests..."
            cd build/
            ./tests
            break
            ;;
        "Just_Forge_Tester")
            echo "Running engine-tester..."
            cd build/
            ./Just_Forge_Tester
            break
            ;;
        "both")
            echo "Running all tests..."
            cd build/
            ./tests
            echo "Running engine-tester..."
            ./Just_Forge_Tester
            break
            ;;
        *) echo "Invalid option $REPLY";;
    esac
done

cd ..
