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
                <form action="bill.php" method="get">
                	<table class="border table-fixed">
                		<tr class="border">
                			<td class="first-letter border">
                				<p>Длина</p>
	                			<div><input name="length" type="radio" value="maxi">Макси</input></div>
    	            			<div><input name="length" type="radio" value="shleif">Макси со шлейфом</input></div>
        	        			<div><input name="length" type="radio" value="midi">Миди</input></div>
            	    			<div><input name="length" type="radio" value="mini">Мини</input></div>
                			</td>
                			<td class="first-letter border">
                				<p>Тип платья</p>
                				<div>
                					<select name="dress_type">
                						<option>Вечернее</option>
	                					<option>Деловое платье</option>
        	        					<option>Брючный костюм</option>
            	    					<option>На выпускной</option>
                					</select>
                				</div>
                			</td>
                			<td class="border">
                				<div class="first-letter">
                					<p>Вид аренды</p>
	                				<div><input name="rent_type" type="radio" value="photo">Фотосессия</input></div>
    	            				<div><input name="rent_type" type="radio" value="event">Мероприятие</input></div>
        	        			</div>
            	    			<div class="first-letter">
                					<p>Дополнительные услуги</p>
                					<div><input type="checkbox" name="shaping">Подгонка по фигуре</input></div>
                					<div><input type="checkbox" name="steaming">Отпаривание</input></div>
                					<div><input type="checkbox" name="packaging">Упаковка</input></div>
	                			</div>
    	            		</td>
        	        	</tr>
            	    	<tr class="border">
                			<td class="border" colspan="3">
                				<div class="first-letter">
                					Ваши данные
                					<table>
                						<tr>
                							<td>Имя:</td>
                							<td><input name="name" type="text"></input></td>
	                					</tr>
    	            					<tr>
        	        						<td>Адрес:</td>
            	    						<td><input name="address" type="text"></input></td>
                						</tr>
                						<tr>
                							<td>E-mail:</td>
                							<td><input name="email" type="text"></input></td>
                						</tr>
                						<tr>
                							<td>Количество дней:</td>
	                						<td><input name="duration" type="text"></input></td>
    	            					</tr>
        	        				</table>
            	    			</div>
                				<p class="first-letter">
                					Файл с базовыми ценами
                					<input type="file" value="../txt/sale.txt"></input>
                				</p>
                				<button>Оформить заказ</button>
	                		</td>
    	            	</tr>
        	        </table>
           	    </form>
            </article>
        </section>
        <footer>
            Copyright &copy; 2020 <a href="/" rel="copyright">Localhost</a>.
            This is the module.
        </footer>
    </div>
</body>
</html>
