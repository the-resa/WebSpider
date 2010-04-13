<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>site1</title>
</head>

<body>
Site1

<ul>
<?php

  for($count = 1; $count < 21; $count++)
  {
	echo '<li><a href="' . $count . '.php">site' . $count . '</a></li>';
  }
  
?>
</ul>

<p><a href="sub/sub.php">Unterseite</a></p>
<p><a href="../index.php">back to index</a></p>
<p><a href="gibts_nicht.php">Diese interne Seite gibts nicht</a></p>
<p><a href="gibts_auch_nicht.php">Diese interne Seite gibts auch nicht</a></p>
<p><img src="../images/lorem_image.jpg" width="240" height="240" alt="lorem image" /></p>
<p><a href="http://www.frick-web.at/de/pics/comic_clash.jpg">Link auf Bild</a></p>
<p><a href="http://www.frick-web.at/de/pics/blub1.jpg">Link auf nicht vorhandenes Bild</a></p>
</body>
</html>