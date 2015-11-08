<?php


function user_max_size ()
{
	$sz = array ();
	if (user('max_file'))
		$sz[] = intval(user('max_file'));
	$sz[] = cfg('max_size');
	
	return min($sz);
}

function ext_allowed ($ext)
{
	if (!cfg('ext_control'))
		return true;
	
	$ext = strtolower(trim($ext));
	$ext_js = array ();
	foreach ($GLOBALS['ext'] as $eg)
	{
		foreach ($eg['d'] as $ed)
		{
			if (in_array($ext, $ed[1])) return true;
		}
	}
	return false;
}

function get_mime_type($filename) 
{
	$mimePath = CORE_PATH.'/mime.types';
	$fileext = substr(strrchr($filename, '.'), 1);
	if (empty($fileext)) return (false);
	$regex = "/^([\w\+\-\.\/]+)\s+(\w+\s)*($fileext\s)/i";
	$lines = (array)@file($mimePath);
	foreach($lines as $line) 
	{
		if (substr($line, 0, 1) == '#') continue; // skip comments
		$line = rtrim($line) . " ";
		if (!preg_match($regex, $line, $matches)) continue; // no match to the extension
		return ($matches[1]);
	}
	return (false); // no match at all
}

function filesize_fix ($path)
{
	exec('du -sb '.escapeshellarg($path), $res);
	$res = @preg_split('/\s+/ims',@$res[0]);
	if (!@$res[0])
		return 0;
	return $res[0];
}

function get_icon ($ext)
{
	if (file_exists(ROOT_PATH.'/tpl/img/file-icons/'.$ext.'.png'))
		return $ext; # Has own image
	
	include_once CORE_PATH.'/ext.php';
	
	foreach ($GLOBALS['ext'] as $gr)
	{
		foreach ($gr['d'] as $e)
		{
			if (in_array($ext, $e[1]))
			{
				// Found!
				// Has group image?
				if (@$e[2])
					return $e[2];
				// Has type image?
				if (@$gr['i'])
					return $gr['i'];
				
				// :(
				return 'download';
			}
		}
	}
	// :(
	return 'download';
}

function time_delete ($tms_add,$tms_del)
{
	$dt_del = date('d.m.Y H:i',$tms_del);
	
	# Calc ttl
	$ttl	= $tms_del - $tms_add;
	$ttln	= $tms_del - time();
	if ($ttln < 0)
	{
		return '<span class="ttl_w_r" title="'.lang('ttl_w_rn').'">'.$dt_del.'</span>';
	}
	
	# Calc % of lfe
	$life_pers = $ttln/$ttl;
	#return ($life_pers.' - '.$ttln.' - '.$ttl);
	if ($life_pers < 0.3)
	{
		return '<span class="ttl_w_r">'.$dt_del.'</span>';
	}
	if ($life_pers < 0.6)
	{
		return '<span class="ttl_w_y">'.$dt_del.'</span>';
	}
	return '<span class="ttl_w_g">'.$dt_del.'</span>';
}

// ------------ lixlpixel recursive PHP functions -------------
// recursive_remove_directory( directory to delete, empty )
// expects path to directory and optional TRUE / FALSE to empty
// of course PHP has to have the rights to delete the directory
// you specify and all files and folders inside the directory
// ------------------------------------------------------------

// to use this function to totally remove a directory, write:
// recursive_remove_directory('path/to/directory/to/delete');

// to use this function to empty a directory, write:
// recursive_remove_directory('path/to/full_directory',TRUE);

function recursive_remove_directory($directory, $empty=FALSE)
{
	// if the path has a slash at the end we remove it here
	if(substr($directory,-1) == '/')
	{
		$directory = substr($directory,0,-1);
	}

	// if the path is not valid or is not a directory ...
	if(!file_exists($directory) || !is_dir($directory))
	{
		// ... we return false and exit the function
		return FALSE;

	// ... if the path is not readable
	}elseif(!is_readable($directory))
	{
		// ... we return false and exit the function
		return FALSE;

	// ... else if the path is readable
	}else{

		// we open the directory
		$handle = opendir($directory);

		// and scan through the items inside
		while (FALSE !== ($item = readdir($handle)))
		{
			// if the filepointer is not the current directory
			// or the parent directory
			if($item != '.' && $item != '..')
			{
				// we build the new path to delete
				$path = $directory.'/'.$item;

				// if the new path is a directory
				if(is_dir($path)) 
				{
					// we call this function with the new path
					recursive_remove_directory($path);

				// if the new path is a file
				}else{
					// we remove the file
					unlink($path);
				}
			}
		}
		// close the directory
		closedir($handle);

		// if the option to empty is not set to true
		if($empty == FALSE)
		{
			// try to delete the now empty directory
			if(!rmdir($directory))
			{
				// return false if not possible
				return FALSE;
			}
		}
		// return success
		return TRUE;
	}
}
// ------------------------------------------------------------

?>