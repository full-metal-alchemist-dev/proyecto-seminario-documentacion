<?php
$servername = "68.66.224.58";
$username = "cat1921ajs_bd";
$password = "&aSI~{{2MyL?";
$dbname = "cat1921ajs_bd";


$conn = new mysqli($servername, $username, $password, $dbname);


if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


$sql = "SELECT status FROM system_config WHERE id = 1"; 
$result = $conn->query($sql);

$status = 0; 
if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $status = $row['status'];
}

$conn->close();


echo $status;
