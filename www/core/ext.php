<?php

$ext = array ();

$ext[] = array (
	't'	=> 'Images',
	'i' => 'jpg',
	'd' => array (
		array('Standart',array('jpg','jpeg','gif','png','tiff'),'jpg'),
		array('Adobe',array('psd','ps','ai'),'jpg')
	)
);
$ext[] = array (
	't'	=> 'Archives',
	'i' => 'rar',
	'd' => array (
		array('Standart',array('zip','gz','tar','rar','7z'),'rar'),
		array('ISO',array('iso','mds','mdf','nrg','vdi'),'iso')
	)
);
$ext[] = array (
	't'	=> 'Documents',
	'i' => 'rtf',
	'd' => array (
		array('Text',array('txt','rtf','htm','html','pdf','csv'),'rtf'),
		array('Open Office',array('odt','ods'),'doc'),
		array('MS Office',array('doc','docx','xls','xlsx','ppt','pptx'),'doc')
	)
);
$ext[] = array (
	't'	=> 'Video',
	'i' => 'avi',
	'd' => array (
		array('Standart',array('avi','mpg','mp4')),
		array('Windows Media',array('wmv')),
		array('Quick Time',array('mov')),
		array('Flash',array('flv'))
	)
);
$ext[] = array (
	't'	=> 'Audio',
	'i' => 'mp3',
	'd' => array (
		array('MP3',array('mp3')),
		array('WAV',array('wav'))
	)
);

$GLOBALS['ext'] = $ext;
?>