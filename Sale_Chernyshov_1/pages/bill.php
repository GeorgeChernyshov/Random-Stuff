<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8"/>
    <title>Шаблоны страниц</title>
    <!--[if IE]>
	<script>
		document.createElement('header');
		document.createElement('nav');
		document.createElement('section');
		document.createElement('article');
		document.createElement('aside');
		document.createElement('footer');
	</script>
<![endif]-->
    <link href="../css/style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <div id="main">
        <section>
             <article>
                <header>
                    <h2>
                        Аренда платья
                    </h2>
                </header>
                <?php 
                    $base_cost = 0;
                    $base_service = 0;
                    $dress_type = "";
                    $dress_type_description = "";
                    $dress_type_cost = 0;
                    $length = "";
                    $length_cost = 0;
                    $additional_services = [];
                    $rent_type = "";
                    $duration = 1;
                    $total_cost = 0;
                    
                    $dress_type_info = [
                        "Вечернее" => [
                            "description" => "Вечернее платье для официальных и неофициальных мероприятий",
                            "cost" => 100,
                        ],
                        "Деловое платье" => [
                            "description" => "Деловое платье в выдержанном стиле, подходящее для деловых встреч",
                            "cost" => 0,
                        ],
                        "Брючный костюм" => [
                            "description" => "Деловой брючный костюм для официальных мероприятий",
                            "cost" => 50,
                        ],
                        "На выпускной" => [
                            "description" => "Платье на выпускной вечер или другое неофициальное мероприятие",
                            "cost" => 10,
                        ],
                    ];
                    
                    $length_info = [
                        "maxi" => [
                            "name" => "Макси",
                            "cost" => 100,
                        ],
                        "schleif" => [
                            "name" => "Макси со шлейфом",
                            "cost" => 150,
                        ],
                        "midi" => [
                            "name" => "Миди",
                            "cost" => 50,
                        ],
                        "mini" => [
                            "name" => "Мини",
                            "cost" => 0,
                        ],
                    ];
                    
                    $additional_services_info = [
                        "shaping" => [
                            "name" => "Подгонка по фигуре",
                            "cost" => 80,
                        ],
                        "steaming" => [
                            "name" => "Отпаривание",
                            "cost" => 30,
                        ],
                        "packaging" => [
                            "name" => "Упаковка",
                            "cost" => 0,
                        ],
                    ];
                    
                    $handle = fopen('../txt/sale.txt', 'r');
                    $data = [];
                    while(!feof($handle))
                    {
                        $dataLine = explode(" ", fgets($handle));
                        $data[$dataLine[0]] = $dataLine[1];
                    }
                    
                    $base_cost = $data["аренда"];
                    $base_service = $data["услуги"];
                    $total_cost = (int)$base_cost;
                    
                    if(isset($_GET["dress_type"]))
                    {
                        $dress_type = $_GET["dress_type"];
                        $dress_type_description = $dress_type_info[$dress_type]["description"];
                        $dress_type_cost = $dress_type_info[$dress_type]["cost"];
                        $total_cost += $dress_type_cost;
                    }
                    
                    if(isset($_GET["length"]))
                    {
                        $length = $length_info[$_GET["length"]]["name"];
                        $length_cost = $length_info[$_GET["length"]]["cost"];
                        $total_cost += $length_cost;
                    }
                    
                    foreach($additional_services_info as $key => $value)
                        if(isset($_GET[$key]))
                            $additional_services[] = $key;
                    
                    foreach($additional_services as $value)
                        $total_cost += (int)$base_service + (int)$additional_services_info[$value]["cost"];
                    
                    if(isset($_GET["rent_type"]))
                    {
                        if($_GET["rent_type"] == "photo")
                            $rent_type = "Фотосессия";
                        elseif($_GET["rent_type"] == "event")
                        {
                            $rent_type = "Мероприятие";
                            $total_cost *= 1.5;
                        }
                    }
                    
                    if(isset($_GET["duration"]) && $_GET["duration"] != "")
                        $duration = $_GET["duration"];
                    
                    $total_cost *= $duration;
                    
                    fclose($handle);
                ?>
                <p class="first-letter">Базовая цена аренды <?=$base_cost ?> рублей</p>
                <p class="first-letter">Базовая цена услуг <?=$base_service ?> рублей</p>
                <table class="border table-wide">
                	<tr class="border">
                		<td class="border">Тип платья</td>
                		<td class="border"><?=$dress_type ?></td>
                		<td class="border">
                			<?php 
                			     if($dress_type_cost != "0")
                			         echo "Наценка: " . $length_cost . " рублей.<br>";
                			     echo $dress_type_description;
                			?>
                		</td>
        	       	</tr>
        	       	<?php 
        	       	   
        	       	?>
            	   	<tr class="border">
                		<td class="border">Длина</td>
                		<td class="border"><?=$length?></td>
                		<td class="border">
                			<?php 
                			    if($length_cost != "0")
                			        echo "Наценка: " . $length_cost . " рублей";
                			?>
                		</td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">Дополнительные услуги</td>
                		<td class="border">
                			<?php 
                		        foreach($additional_services as $value)
                		            echo $additional_services_info[$value]["name"] . '<br>';
                		    ?>
                		</td>
                		<td class="border">
                			<?php 
                		        foreach($additional_services as $value)
                		            echo $base_service + $additional_services_info[$value]["cost"] . ' рублей<br>';
                		    ?>
                		</td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">Вид аренды</td>
                		<td class="border" colspan="2"><?=$rent_type?></td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">Фамилия заказчика</td>
                		<td class="border" colspan="2"><?=$_GET["name"]?></td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">Адрес</td>
                		<td class="border" colspan="2"><?=$_GET["address"]?></td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">E-mail</td>
                		<td class="border" colspan="2"><?=$_GET["email"]?></td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">Количество дней</td>
                		<td class="border" colspan="2"><?=$duration?></td>
        	       	</tr>
        	       	<tr class="border">
                		<td class="border">Итого</td>
                		<td class="border" colspan="2">
                			<?php
                			    echo 'Цена за ' . $duration;
                			    if($duration == 1)
                			        echo ' день';
                			    else
                			        echo ' дня';
                			    echo ' аренды ' . $total_cost . ' рублей.';
                		    ?>
                		</td>
        	       	</tr>
        	    </table>
            </article>
        </section>
        <footer>
            Copyright &copy; 2020 <a href="/" rel="copyright">Localhost</a>.
            This is the module.
        </footer>
    </div>
</body>
</html>
