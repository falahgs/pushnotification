<?php
header('Expires: Mon, 26 Jul 2018 05:00:00 GMT');
header('Cache-Control: no-store, no-cache, must-revalidate');
header('Cache-Control: post-check=0, pre-check=0', FALSE);
header('Pragma: no-cache');
  require("lib/instapush.php");
  
        $ip = InstaPush::getInstance("58b55601a4c48afa0e78cd27", "fab1a4bfd66306e5b84e3d949965a484");
        $ip->track("alarm", array( 
                "alarmesp8266"=> "sami"
				
        )); 
		//echo rand(5, 15);
?>