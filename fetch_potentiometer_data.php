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

// SQL query to fetch potentiometer data
$sql = "SELECT id, pot_value, recorded_at FROM potentiometer_data ORDER BY recorded_at ASC ";  // Fetch all data ordered by timestamp
$result = $conn->query($sql);

// Initialize an array to hold the fetched data
$data = [];

if ($result->num_rows > 0) {
    // Loop through all rows and add them to the data array
    while ($row = $result->fetch_assoc()) {
        $data[] = [
            'id' => $row['id'],
            'pot_value' => (float)$row['pot_value'],  // Cast to float for consistency
            'recorded_at' => $row['recorded_at']     // Date and time of the reading
        ];
    }
}

// Close the connection
$conn->close();

// Set response header to JSON and return the data
header('Content-Type: application/json');
echo json_encode($data);
