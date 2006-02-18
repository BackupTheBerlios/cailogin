#!/bin/bash
echo Content-type: text/html
echo ""

EXECBIN=/usr/local/bin/cailogin

cat << EOF
<html>
<head>
<title>Test CAILogin</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>
<body>
EOF

if [ "$REQUEST_METHOD" = "GET" ] && [ "$QUERY_STRING" != "" ]; then
	ImageID=`echo $QUERY_STRING | sed "s/.*imageid=\([0-9]*\).*/\1/g"`
	Code=`echo $QUERY_STRING | sed "s/.*code=\([0-9]*\).*/\1/g"`
	
	if $EXECBIN -c $ImageID $Code > /dev/null 2> /dev/null; then
		echo '<br/><br/><div align="center"><h2>OK</h2></div></body></html>'
	else	
		echo '<br/><br/><div align="center"><h2>Access Code Mismatch!</h2></div></body></html>'
	fi
	exit
else
ImageID=$RANDOM
$EXECBIN -r $ImageID > /dev/null

cat << EOF
<div align="center">
<h2>Secure Login Form with CAILogin</h2>
</div><br/>
<form action="login.cgi" method="get" name="CAILogin">
 <table width="500" border="0" align="center" cellpadding="0" cellspacing="2">
  <tr>
   <td width="150">Username</td>
   <td><input name="username" type="text"/></td>

  </tr>
  <tr>
   <td width="150">Password</td>
   <td><input name="password" type="password"/></td>
  </tr>
  <tr>
   <td width="150">Access Code</td>
   <td>
   	<table><tr><td bgcolor="#ff0000">
	<input name="code" type="text" value=""/></td>
	<td>&nbsp;&nbsp;<img src="cailogin.cgi?$ImageID"/></td></tr>
	</table>
   </td>
  </tr>

  <tr>
   <td width="150">&nbsp;<input name="imageid" type="hidden" value="$ImageID"/></td>
   <td><input name="submit" type="submit" value="Login"></td>
  </tr>
 </table>
</form>
<div align="center">
<br/><b>Note: </b><small>The underlying cgi script is a simple bash script, that you can find in CAILogin's sources.</small>
</div>
</body>

</html>
EOF

fi
