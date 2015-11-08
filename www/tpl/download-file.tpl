<table width="100%" cellpadding="5">
	<tr>
		<th width="150" align="right">{{$lang.fd_uploaded_by}}:</th>
		<td>{{$u_data.user}}</td>
	</tr>
	<tr>
		<th align="right">{{$lang.fd_uploaded}}:</th>
		<td>{{$u_data.time_added}}</td>
	</tr>
	<tr>
		<th align="right">{{$lang.fd_until}}:</th>
		<td>{{$u_data.time_del}}</td>
	</tr>
	<tr>
		<th align="right">{{$lang.fd_descr}}:</th>
		<td id="descr_area">{{$u_data.descr}}</td>
	</tr>
</table>
{{if $own}}
<div id="edit_btns">
	<center>
		<input type="button" name="sub_edit" value="{{$lang.edit}}" onclick="do_edit();"/>
		<input type="button" name="sub_del" value="{{$lang.delete}}" onclick="do_del();"/>
	</center>
</div>
<div id="edit_area" style="display:none;">
<form method="post" action="?k={{md5(user('lk'))}}">
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
				&nbsp;&nbsp;
				<label><input type="checkbox" value="ON" name="files_ttl_prol" id="files_ttl_prol" {{if $u_data.prolong=='Y'}}checked="checked"{{/if}}/> {{$lang.ttl_prol}}</label>
			</td>
		</tr>
	</table>
	<center><input type="submit" name="sub_edit" value="{{$lang.save}}"/></center>
<form>
</div>

<script type="text/javascript">
function do_edit()
{
	$('#files_descr').attr('value',$('#descr_area').html());
	$('#edit_btns').hide();
	$('#edit_area').show();
}
function do_del()
{
	if (confirm('{{$lang.delete_c}}'))
		document.location.href='?del=1&k={{md5(user('lk'))}}';
}
</script>

{{/if}}
{{if $own}}
	<hr/>
	<table width="100%" cellpadding="5">
		<tr>
			<td>{{$lang.fd_publink_d}} : <a href="{{$u_data.publink}}">{{$lang.fd_publink}}</a></td>
		</tr>
	</table>
	<hr/>
{{/if}}

<h3>{{$lang.fd_file_list}}:</h3>
{{$f_list}}