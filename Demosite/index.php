<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Webcrawler Demosite</title>
</head>

<body>

<h1>Willkommen auf der Webcrawler Demosite!</h1>

<h2>Unterseiten</h2>
<ul>
<?php

  for($count = 1; $count < 21; $count++)
  {
    echo "<li><a href='sites/" . $count . ".php'>site" . $count . "</a></li>";
  }
  
?>
</ul>

<h2> Links mit redirects </h2>

<p><a href="redirects/redirect1.php">Redirect-Seite1: redirect zum Index</a></p>
<p><a href="redirects/redirect2.php">Redirect-Seite2: redirect zu google.at</a></p>
<p><a href="redirects/redirect3.php">Redirect-Seite3: redirect zu Redirect-Seite3</a></p>
<p><a href="redirects/redirect4.php">Redirect-Seite4: redirect zu Redirect-Seite3</a></p>

<h2> Diverse Links </h2>

<p><a href="sites/gibts_nicht.php">Diese interne Seite gibts nicht</a></p>
<p><a href="sites/gibts_auch_nicht.php">Diese interne Seite gibts auch nicht</a></p>
<p><a href="www.google.at">Google ohne http</a></p>
<p><a href="http://www.google.at">Google mit http</a></p>
<p><a href="www.yahoo.de">Yahoo ohne http</a></p>
<p><a href="http://www.yahoo.de">Yahoo mit http</a></p>
<p><a href="http://www.flikr.com">Flikr</a></p>
<p><a href="http://www.facebook.com">Facebook</a></p>
<p><a href="http://www.frick-web.at/de/pics/comic_clash.jpg">Link auf Bild</a></p>
<p><a href="http://www.frick-web.at/de/pics/blub.jpg">Link auf nicht vorhandenes Bild</a></p>
<p><img src="images/lorem_image.jpg" width="240" height="240" alt="lorem image" /></p>

<h2>Broken Links Webcrawler Demosite (interne broken links)</h2>
<ul>
<?php

  for($count_broken = 1; $count_broken < 201; $count_broken++)
  {
    echo "<li><a href='sites/broken/" . $count_broken . ".php'>broken_intern" . $count_broken . "</a></li>";
  }
  
?>
</ul>

<h2>Broken Links anderer Websites (externe broken links)</h2>
<ul>
<?php

  for($count_broken = 1; $count_broken < 201; $count_broken++)
  {
    echo "<li><a href='http://www.frick-web.at/sites/broken/" . $count_broken . ".php'>broken_extern" . $count_broken . "</a></li>";
  }
  
?>
</ul>
