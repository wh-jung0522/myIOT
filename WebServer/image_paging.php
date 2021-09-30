<?php
$folder = '/home/whjung/Data/WH/Exmaple_Tumbnail/';
$filetype = '*.*';    
$files = glob($folder.$filetype);    
$total = count($files);    
$per_page = 6;    
$last_page = (int)($total / $per_page);    
if(isset($_GET["page"])  && ($_GET["page"] <=$last_page) && ($_GET["page"] > 0) ){
    $page = $_GET["page"];
    $offset = ($per_page + 1)*($page - 1);      
}else{
    echo "Page out of range showing results for page one";
    $page=1;
    $offset=0;      
}    
$max = $offset + $per_page;    
if($max>$total){
    $max = $total;
}
//print_r($files);
echo "Processsing page : $page offset: $offset max: $max total: $total last_page: $last_page";        
show_pagination($page, $last_page);        
for($i = $offset; $i< $max; $i++){
    $file = $files[$i];
    $path_parts = pathinfo($file);
    $filename = $path_parts['filename'];        
    echo '        
    <div class="galleryCellHolder">
        <div class="galleryCell">
            <a class="fancybox" rel="group" href="'.$file.'"><img class="galleryPhoto" src="'.$file.'" alt="'.$filename.'"></a>
        </div>
    </div>        
    ';                
}        
show_pagination($page, $last_page);

function show_pagination($current_page, $last_page){
    echo '<div>';
    if( $current_page > 1 ){
        echo ' <a href="?page='.($current_page-1).'"> &lt;&lt;Previous </a> ';
    }
    if( $current_page < $last_page ){
        echo ' <a href="?page='.($current_page+1).'"> Next&gt;&gt; </a> ';  
    }
    echo '</div>';
}
?>
<a href="./index.php">Prev Page</a><br>