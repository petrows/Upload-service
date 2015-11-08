<table width="100%" cellpadding="3" cellspacing="0">
	<tr>
		<td rowspan="2" width="100" align="center" valign="top"><a href="{{$f_link}}" target="_blank" style="border:none;"><img src="{{$_url}}/tpl/img/file-icons/{{$f_icon}}.png"/></a></td>
		<td class="flist-fname"><a href="{{$f_link}}" target="_blank">{{$f.name}}</a></td>
		<td class="flist-size">{{$f.size}}</td>
	</tr>
	<tr>
		<td colspan="2" valign="top" align="left">
			<table width="100%" cellpadding="3">
				<tr>
					<th width="50" align="right">{{$lang.fld_link}}:</th>
					<td class="flist-flink"><a href="{{$f_link}}" target="_blank">{{$f_link}}</a></td>
				</tr>
				<tr>
					<th align="right">{{$lang.fld_link_f}}:</th>
					<td class="flist-flink"><a href="{{$f_link_f}}" target="_blank">{{$f_link_f}}</a></td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<br/>