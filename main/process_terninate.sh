# Find the PIDs of the running processes
PIDS=$(pgrep -f "python server.py|./fusionT|python CAN_LOG.py")

# If no processes are found, exit the script
if [ -z "$PIDS" ]; then
    echo "No matching processes found"
    exit 1
fi

# Terminate the processes
kill $PIDS

# Confirm that the processes are terminated
if [ $? -eq 0 ]; then
    echo "Processes terminated successfully"
else
    echo "Failed to terminate processes"
fi