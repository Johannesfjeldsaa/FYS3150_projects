#! /bin/sh

cd build

if [ ! -d ../output ]; then
  mkdir ../output
fi

run_program() {
    # Define local variables
    local program=$1
    local outputfile=$2
    local write_errors=false
    local write_errors_separately=false
    local error_redirect=""
    local error_file=""
    local redirect_command=">"
    
    # Check for --write-errors and --write-errors-separately flags
    for arg in "$@"; do
        if [ "$arg" = "--write-errors" ]; then
            write_errors=true
            error_redirect="2>&1"
            break
        elif [ "$arg" = "--write-errors-separately" ]; then
            write_errors_separately=true
            error_file="${outputfile%.*}_error.out"
            break
        fi
    done

    # Check if output file already exists and prompt user to overwrite or append
    if [ -f "$outputfile" ]; then
        echo -n "The file $outputfile already exists. Overwrite (y/n) or append (a)? "
        read reply
        case $reply in
            [Yy])
                echo "Overwriting $outputfile"
                ;;
            [Aa])
                echo "Appending to $outputfile"
                redirect_command=">>"
                ;;
            *)
                echo "Skipping."
                return
                ;;
        esac
    else
        echo "$outputfile does not exist. Creating a new file."
    fi

     # Echo handling of errors
    if [ "$write_errors" = true ]; then
        echo "Writing both stdout and stderr to $outputfile"
    elif [ "$write_errors_separately" = true ]; then
        echo "Writing stdout to $outputfile and stderr to $error_file"
    else
        echo "Writing stdout to $outputfile"
    fi

     # Execute the command with appropriate redirections
    if [ "$write_errors_separately" = true ]; then
        eval ./"$program" "$redirect_command" "$outputfile" 2"$redirect_command" "$error_file"
        if [ -z "$error_file" -o ! -s "$error_file" ]; then
            rm -f "$error_file"
        fi
    else
        eval ./"$program" "$redirect_command" "$outputfile" "$error_redirect"
    fi
}

run_program "test" "../output/test.out" --write-errors-separately

