select good.name, category.name from good
	inner join category_has_good on good.id = category_has_good.good_id
	inner join category on category_has_good.category_id = category.id
    order by good.name, category.name
