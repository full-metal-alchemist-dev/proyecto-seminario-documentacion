<?php
$servername = "68.66.224.58";
$username = "cat1921ajs_bd";
$password = "&aSI~{{2MyL?";
$dbname = "cat1921ajs_bd";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}




$sql = "SELECT * FROM system_config WHERE id = 1 ";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Fetch the row and get the status value
    $row = $result->fetch_assoc();
    echo $row['status'];
} else {
    // If no rows found, return an appropriate message
    echo "No status found";
}

$conn->close();
