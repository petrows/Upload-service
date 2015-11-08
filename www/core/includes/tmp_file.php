<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/* generate proxy list for test */

$c_list = array('RU','US','AG','GB','AU');

for ($x=0, $n=0, $s=0; $x<10; $x++)
{
	if ($n>254)
	{
		$n = 0;
		$s++;
	} else {
		$n++;
	}

	$db_data = array ();
	$db_data['proxy']			= '127.0.'.$s.'.'.$n;
	$db_data['port']			= mt_rand(1024,65000);
	$db_data['tms_add']			= time () - mt_rand (0, 2343243);
	$db_data['tms_last_check']	= $db_data['tms_add'] + mt_rand (0, 23222);
	$db_data['used_c']			= 0;
	$db_data['country']			= $c_list[array_rand($c_list)];
	$db_data['speed']			= 1000/mt_rand(1,1000);
	$db_data['is_mt']			= (mt_rand(0,10)>5?'Y':'N');

	db_insert('proxy', $db_data);
}
?>