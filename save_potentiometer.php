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

// // Get potentiometer value from query parameter
// $potValue = isset($_GET['potValue']) ? (float)$_GET['potValue'] : 0.0;  // Potentiometer value as a decimal

// // Prepare and execute SQL to insert potentiometer value into the database
// $sql = "INSERT INTO potentiometer_data (pot_value, recorded_at) VALUES (?, NOW())";
// $stmt = $conn->prepare($sql);
// $stmt->bind_param("d", $potValue);  // Bind the potentiometer value as a double (decimal)
// $stmt->execute();

// // Prepare response
// $response = ['success' => $stmt->affected_rows > 0];
// $stmt->close();
// $conn->close();

// // Return JSON response
// header('Content-Type: application/json');
// echo json_encode($response);



// <?php
// include 'db_connection.php';  // Include your database connection

// Get potentiometer value from query parameter
//$potValue = isset($_GET['potValue']) ? (float)$_GET['potValue'] : 0.0;  // Potentiometer value as a decimal
$potValue = $_GET['potValue'];  // Potentiometer value as a decimal

// Debugging: Log received value
file_put_contents('log.txt', "Received potentiometer value: " . $potValue . "\n", FILE_APPEND);

// Prepare and execute SQL to insert potentiometer value into the database
$sql = "INSERT INTO potentiometer_data (pot_value, recorded_at) VALUES (?, NOW())";
$stmt = $conn->prepare($sql);
$stmt->bind_param("d", $potValue);  // Bind the potentiometer value as a double (decimal)
$stmt->execute();

// Check for errors
if ($stmt->error) {
  file_put_contents('log.txt', "SQL Error: " . $stmt->error . "\n", FILE_APPEND);
}

$stmt->close();
$conn->close();
?>