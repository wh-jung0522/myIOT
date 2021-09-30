<?php 
$image_dir = $_GET['image_dir'];
if ($handle = opendir($image_dir)) { 

   /* This is the correct way to loop over the directory. */ 

   while (false !== ($image = readdir($handle))) { 

      if ($image != '.' && $image != '..'){ 
        echo 
        "<figure>
            <a href='$image_dir/$image' title='origin'>
            <img src='$image_dir/$image' width='100' height='100' />
            <figcaption> 파일명 : $image</figcaption>
         </figure>"; 
      } 
   } 
   closedir($handle); 
} 
?>
<a href="./image_paging_test.php">Prev Page Test</a><br>