select good.name from good
	inner join category_has_good on good.id = good_id
	inner join category on category.id = category_id
	where category.name = "Cakes"
union
select good.name from good
	inner join sale_has_good on good.id = good_id
	inner join saleon sale.id = sale_id
	inner join status on status.id = sale.status_id
	where status.name = "delivering";
