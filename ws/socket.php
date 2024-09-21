<?php
require '../vendor/autoload.php';

use Ratchet\Server\IoServer;
use Ratchet\Http\HttpServer;
use Ratchet\WebSocket\WsServer;
use Ratchet\Http\OriginCheck;

$server = IoServer::factory(
    new HttpServer(
        new WsServer(
            new HttpRequestLogger()
        )
    ),
    8080
);

$server->run();
