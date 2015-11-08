<?php

$ttl = array ();

$ttl[3600]	= lang('ttl_h');
$ttl[86400] = lang('ttl_d');
$ttl[5*86400] = lang('ttl_5d');
$ttl[7*86400] = lang('ttl_7d');
$ttl[15*86400] = lang('ttl_15d');
$ttl[30*86400] = lang('ttl_30d');
$ttl[3*30*86400] = lang('ttl_3m');

$GLOBALS['ttl'] = $ttl;
$GLOBALS['ttl_def'] = 86400;
?>