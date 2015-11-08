<script type="text/javascript" src="{{$_url}}/tpl/file-upload/fileuploader.js"></script>

<noscript>
	<div id="js_not_support">
		<p>{{$lang.fl_jsn_text}}</p>
		<h4><a href="#">{{$lang.fl_jsn_s_form}}</a></h4>
	</div>
</noscript>

<div id="xhr_not_support" style="display:none;">
	<h3>{{$lang.fl_xhrsn_title}}</h3>
	<p>{{$lang.fl_xhrsn_text}}</p>
	<h4><a href="#">{{$lang.fl_xhrsn_s_form}}</a></h4>
</div>

<div id="upload_area" style="display:none;">
	<p>
		{{if cfg('ext_control')}}
			<h3 class="p_title">{{$lang.fl_allow_ext}}:</h3>
			{{$ext_t}}
		{{/if}}
	</p>
	<br clear="all"/>
	<div id="upl-btn">{{$lang.fl_upload_btn}} <p style="padding:5px;margin:0px;"><small>{{$lang.fl_max_size_s}}: <b>{{format_size($max_size)}}</b></small></p></div>
	<br clear="all"/>
	<table id="upl-list" width="100%">
		<tr>
			<th width="50">#</th>
			<th>{{$lang.fl_file_name}}</th>
			<th width="120">{{$lang.fl_file_size}}</th>
			<th width="300">{{$lang.fl_file_upl_s}}</th>
		</tr>
	</table>



	<div id="file-uploader" style="display:none;">
		<noscript>			
			<p>Please enable JavaScript to use file uploader.</p>
			<!-- or put a simple form for upload here -->
		</noscript>         
	</div>

	<ul id="file-list"></ul>
	<div id="file-continue" style="display:none;">
		<form method="post" action="{{$_url}}/upload/final/?s={{$sid}}" onsubmit="return final_upload()">
			<div id="file-continue-form">
				<table width="100%" cellpadding="5">
					<tr>
						<th align="right" width="200">{{$lang.fl_descr}}:</th>
						<td align="left">
							<input type="text" name="files_descr" id="files_descr" placeholder="{{$lang.fl_descr_c}}" style="width:98%"/>
						</td>
					</tr>
					<tr>
						<th align="right">{{$lang.fl_ttl}}:</th>
						<td align="left">
							<select name="files_ttl" id="files_ttl">{{$ttl_sel}}</select>
						</td>
					</tr>
					<tr>
						<th align="right"></th>
						<td align="left">
							<label><input type="checkbox" value="ON" name="files_ttl_prol" id="files_ttl_prol"/> {{$lang.ttl_prol}}</label>
						</td>
					</tr>
				</table>
			</div>
		<input id="file-continue-btn" type="submit" value="..." onclick="final_upload();"/>
		</form>
	</div>
</div>
<script type="text/javascript">    
	function createUploader()
	{   
		if (!is_xhr_support())
		{
			$('#xhr_not_support').show();
			$('#upload_area').hide();
			return;
		}
		$('#upload_area').show();
		window.__uploader = new qq.FileUploader({
			element: document.getElementById('file-uploader'),
			action: '{{$_url}}/upload.cgi',
			params: {'s':'{{$sid}}'},
			{{if cfg('ext_control')}}
				allowedExtensions: [{{$ext_js}}],
			{{/if}}
			button: document.getElementById('upl-btn'),
			//listElement: document.getElementById('file-list'),
			//template: '',
			fileTemplate: '<li>' +
                '<span class="qq-upload-file"></span>' +
                '<span class="qq-upload-spinner"></span>' +
                '<span class="qq-upload-size"></span>' +
                '<a class="qq-upload-cancel" href="#">Cancel</a>' +
                '<span class="qq-upload-failed-text">Failed</span>' +
            '</li>',      
			sizeLimit: {{$max_size}},
			debug: true,
			messages: {
				typeError: "{{$lang.fl_e_type}}",
				sizeError: "{{$lang.fl_e_size}}",
				minSizeError: "{{$lang.fl_e_minsize}}",
				emptyError: "{{$lang.fl_e_empty}}",
				onLeave: "{{$lang.fl_e_leave}}"            
			},
			showMessage: function(message){
				alert(message);
			},
			onSubmit: function(id, fileName)
			{
				// window.__uploader.params['ttl'] = $('#files_ttl').val();
				c_btn_status(false);
				upl_new(id,fileName);
				return true;
			},
			onProgress: function(id, fileName, loaded, total)
			{
				c_btn_status(!c_upload_status());
				upl_progress(id,fileName,loaded,total);
			},
			onComplete: function(id, fileName, responseJSON)
			{
				c_btn_status(!c_upload_status());
				upl_done(id, fileName, responseJSON);
			}
		});
	}
	
	
	
	// in your app create uploader as soon as the DOM is ready
	// don't wait for the window to load  
	window.onload = createUploader;
	
	if(document.getElementsByClassName) {

		getElementsByClass = function(classList, node) {    
			return (node || document).getElementsByClassName(classList)
		}

	} else {

		getElementsByClass = function(classList, node) {			
			var node = node || document,
			list = node.getElementsByTagName('*'), 
			length = list.length,  
			classArray = classList.split(/\s+/), 
			classes = classArray.length, 
			result = [], i,j
			for(i = 0; i < length; i++) {
				for(j = 0; j < classes; j++)  {
					if(list[i].className.search('\\b' + classArray[j] + '\\b') != -1) {
						result.push(list[i])
						break
					}
				}
			}

			return result
		}
	}
	
	function is_xhr_support ()
	{
		var input = document.createElement('input');
		input.type = 'file'; 
		
		return (
			'multiple' in input &&
			typeof File != "undefined" &&
			typeof (new XMLHttpRequest()).upload != "undefined" );
	}
	
	function formatSize (bytes)
	{
		// bytes = bytes.MAX_VALUE;
        var i = -1;                                    
        do {
            bytes = bytes / 1024;
            i++;
        } while (bytes > 1024);
        
        return Math.max(bytes, 0.01).toFixed(2) + '&nbsp;' + ['kB', 'MB', 'GB', 'TB', 'PB', 'EB'][i];          
    }
    
    // alert (formatSize(100500100500123456789));
	
	function row2id (id)
	{
		var itm = document.getElementById('upl-list').firstChild;
		while (itm)
		{            
			if (itm.fileId == id) return itm;            
			itm = itm.nextSibling;
        }
	}
	
	function upl_new (id, fileName)
	{
		var row = document.createElement('tr');
		fileName.replace(/</g,'&lt;');
		fileName.replace(/>/g,'&gt;');
		// alert(fileName);
		
		var td;
		td = document.createElement('td');
		td.className = "ulist-id";
		td.innerHTML = (id+1);
		row.appendChild(td);
		td = document.createElement('td');
		td.className = "ulist-name";
		td.innerHTML = fileName;
		row.appendChild(td);
		td = document.createElement('td');
		td.className = "ulist-size";
		td.innerHTML = ' - ';
		row.appendChild(td);
		td = document.createElement('td');
		td.className = "ulist-status";
		td.innerHTML = ' - ';
		row.appendChild(td);
		
		//row.innerHTML = '<td class="ulist-id">'+(id+1)+'</td><td class="ulist-name">'+fileName+'</td><td class="ulist-size">-</td><td class="ulist-status">-</td>';
		row.fileId = id;
		document.getElementById('upl-list').appendChild(row);
	}	
	function upl_progress (id, fileName, loaded, total)
	{
		var row = row2id(id);
		if (!row) return;
		
		getElementsByClass('ulist-size',row)[0].innerHTML = formatSize(loaded) + ' / ' + formatSize(total);
		
		var pers = Math.round(loaded / total * 100);
		var sz = (200/100)*pers;
		getElementsByClass('ulist-status',row)[0].innerHTML = '{{$lang.fl_s_loading}}: <b>'+pers+'</b>% '+make_progress_bar(pers);
	}
	function make_progress_bar(pers)
	{
		var out = '';
		out += '<span class="ulist-progress"><span class="ulist-progress-bar" style="width:'+pers+'%;"><img src="{{$_url}}/tpl/img/spacer.gif" alt=""/></span></span>';
		
		return out;
	}
	function upl_done (id, fileName, responseJSON)
	{
		var row = row2id(id);
		if (!row) return;
		
		if (responseJSON['success'])
		{
			// Upload is OK!
			getElementsByClass('ulist-status',row)[0].innerHTML = '<span class="ulist-s-ok">{{$lang.fl_s_loaded}}</span>';
			return;
		}
		if (responseJSON['error'])
		{
			// Upload is OK!
			getElementsByClass('ulist-status',row)[0].innerHTML = '<span class="ulist-s-error">{{$lang.fl_s_error}}: '+responseJSON['error']+'</span>';
			return;
		}
		
		getElementsByClass('ulist-status',row)[0].innerHTML = '<span class="ulist-s-error">{{$lang.fl_s_uerror}}</span>';
	}
	
	function c_upload_status ()
	{
		return window.__uploader.getInProgress();
	}
	function c_btn_status (enabled)
	{
		$('#file-continue').css('display','');
		if (enabled)
		{
			$('#file-continue-btn').removeAttr('disabled');
			$('#file-continue-btn').attr('value',' {{$lang.fl_btn_continue}} ');
		} else {
			$('#file-continue-btn').attr('disabled','disabled');
			$('#file-continue-btn').attr('value',' {{$lang.fl_btn_wait}} ');
		}
	}	
	
	function final_upload ()
	{
		if (c_upload_status()) return false;
		return true;
	}
</script>
