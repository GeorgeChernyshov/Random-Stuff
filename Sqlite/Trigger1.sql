delimiter //
create trigger on_update_sale
	 after update 
     on sale for each row
begin
	call update_sale(new.id, new.status_id);
end
//
