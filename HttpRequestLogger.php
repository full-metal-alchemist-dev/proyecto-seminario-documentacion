<?php
use Ratchet\MessageComponentInterface;
use Ratchet\ConnectionInterface;
use Psr\Http\Message\RequestInterface;

class HttpRequestLogger implements MessageComponentInterface {
    protected $clients;

    public function __construct() {
        $this->clients = new \SplObjectStorage;
    }

    public function onOpen(ConnectionInterface $conn, RequestInterface $request = null) {
        // Store the new connection
        $this->clients->attach($conn);

        // Retrieve client IP address using the request object
        $clientIp = $request ? $request->getHeader('X-Forwarded-For')[0] ?? $conn->remoteAddress ?? 'Unknown' : 'Unknown';

        // Log the connection with client IP address
        echo "New connection from IP: {$clientIp}\n";
    }

    public function onMessage(ConnectionInterface $from, $msg) {
        // Broadcast the message to all connected clients
        foreach ($this->clients as $client) {
            if ($from !== $client) {
                $client->send($msg);  // Send the message to all clients except the sender
            }
        }
    }

    public function onClose(ConnectionInterface $conn) {
        // Detach the connection when closed
        $this->clients->detach($conn);

        echo "Connection closed\n";
    }

    public function onError(ConnectionInterface $conn, \Exception $e) {
        echo "Error: {$e->getMessage()}\n";
        $conn->close();
    }
}
