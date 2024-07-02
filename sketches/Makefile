CC := gcc
CFLAGS := -I/usr/local/include
LDFLAGS := -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

basic_window: basic_window.c
	$(CC) -o basic_window basic_window.c $(CFLAGS) $(LDFLAGS)

bouncing_ball: bouncing_ball.c
	$(CC) -o bouncing_ball bouncing_ball.c $(CFLAGS) $(LDFLAGS)

mouse_drag_draw_shape: mouse_drag_draw_shape.c
	$(CC) -o mouse_drag_draw_shape mouse_drag_draw_shape.c $(CFLAGS) $(LDFLAGS)

basic_shapes: basic_shapes.c
	$(CC) -o basic_shapes basic_shapes.c $(CFLAGS) $(LDFLAGS)

circle_sector_gui: circle_sector_gui.c
	$(CC) -o circle_sector_gui circle_sector_gui.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f basic_window bouncing_ball mouse_drag_draw_shape basic_shapes circle_sector_gui