<?php

$memcache = new \Memcache;
$memcache->addServer('127.0.0.1', 11211, true, 5, 1, 60);

for($i=0; $i<100000; $i++) {
  $memcache_k = "memcache." + $i;
  $memcache->set($memcache_k, $i, 0, 0);
}
