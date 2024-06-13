#!/bin/bash

# Directory containing log files
LOG_DIR="/Users/md.rakibulislam/IIT Life/CSE-401(LabFinal)/user_logs"

# Temporary file to hold the summary data
TEMP_FILE=$(mktemp)

# Report file
REPORT_FILE="login_summary.txt"

# Initialize variables to track the date with the highest and lowest unique logins
highest_unique_logins=0
highest_unique_login_date=""
lowest_unique_logins=0
lowest_unique_login_date=""

# Create or clear the report file
echo "Daily Unique User Logins Report" > "$REPORT_FILE"
echo "===============================" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

# Process each log file
for file in "$LOG_DIR"/log_*.txt; { #do
    # Extract the date from the filename
    date=$(basename "$file" | sed 's/log_\([0-9]\{8\}\)\.txt/\1/')

    # Count unique logins for the current file
    unique_logins=$(sort "$file" | uniq | wc -l)

    # Append the date and unique login count to the temporary file
    echo "$date $unique_logins" >> "$TEMP_FILE"

    # Update highest and lowest unique logins
    if [[ $unique_logins -gt $highest_unique_logins ]]; then
        highest_unique_logins=$unique_logins
        highest_unique_login_date=$date
    fi

    if [[ $lowest_unique_logins -eq 0 || $unique_logins -lt $lowest_unique_logins ]]; then
        lowest_unique_logins=$unique_logins
        lowest_unique_login_date=$date
    fi
}

# Append the unique login counts per day to the report
cat "$TEMP_FILE" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

# Append the date with the highest number of unique logins to the report
echo "Date with the highest number of unique logins:- Date= $highest_unique_login_date ($highest_unique_logins unique logins)" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

# Append the date with the lowest number of unique logins to the report
echo "Date with the lowest number of unique logins:- Date= $lowest_unique_login_date ($lowest_unique_logins unique logins)" >> "$REPORT_FILE"

# Clean up the temporary file
rm "$TEMP_FILE"

# Print a message indicating where the report is saved
echo "Report generated: $REPORT_FILE"
open "$REPORT_FILE"

