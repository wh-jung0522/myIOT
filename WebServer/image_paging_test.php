<?php
$folder_path = null;
$user = $_GET['user'];
switch($user)
{
    case 'Woohyun':
        $folder_path = './Data/WH';
        break;
    case 'Sooman':
        $folder_path = './Data/SM';
        break;
    case 'Eunhee':
        $folder_path = './Data/MOM';
        break;
    default:
        $folder_path = null;
        break;
}
if($folder_path == null){
    echo "<h1> Bad Access! </h1><br>";
}
else{
    if($folder = opendir($folder_path));
    {
        while(false !== ($sub_folder = readdir($folder)))
        {
            if($sub_folder != '.' && $sub_folder != '..')
            {
                $image_dir = "$folder_path/$sub_folder";
                echo "<a href='./show_image.php?image_dir=$image_dir'>$sub_folder</a><br>";
            }
        }

    }
}
?>
<a href="./index.php">Prev Page</a><br>