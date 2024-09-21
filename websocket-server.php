<?php
require 'vendor/autoload.php';

use Ratchet\MessageComponentInterface;
use Ratchet\ConnectionInterface;
use Ratchet\WebSocket\WsServer;
use Ratchet\Http\HttpServer;
use Ratchet\Server\IoServer;
use React\EventLoop\Factory;
use React\Socket\SecureServer;
use React\Socket\Server as ReactServer;

class WebSocketServer implements MessageComponentInterface
{
    protected $clients;

    public function __construct()
    {
        $this->clients = new \SplObjectStorage;
    }

    public function onOpen(ConnectionInterface $conn)
    {
        $this->clients->attach($conn);
        echo "New connection: ({$conn->resourceId})\n";
    }

    public function onMessage(ConnectionInterface $from, $msg)
    {
        echo "Message received: $msg\n";
        foreach ($this->clients as $client) {
            if ($from !== $client) {
                $client->send($msg);
            }
        }
    }

    public function onClose(ConnectionInterface $conn)
    {
        $this->clients->detach($conn);
        echo "Connection closed: ({$conn->resourceId})\n";
    }

    public function onError(ConnectionInterface $conn, \Exception $e)
    {
        echo "Error: {$e->getMessage()}\n";
        $conn->close();
    }
}

// Set up SSL/TLS context
$loop = Factory::create();
$webSock = new ReactServer('68.66.224.58:8080', $loop);
$secureServer = new SecureServer($webSock, $loop, [
    'local_cert' => '/path/to/ssl/certificate.pem',
    'local_pk' => '/path/to/ssl/private.key'
]);

$webSocketServer = new WsServer(new WebSocketServer());
$httpServer = new HttpServer($webSocketServer);

$ioServer = new IoServer($httpServer, $secureServer, $loop);
$ioServer->run();
