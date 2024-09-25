NAME := cub3D

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

VPATH :=	src \
			src/cub \
			src/analyser \
			src/draw \
			src/handlers \
			src/map \
			src/sprite \
			src/state_machine \
			src/utility

BUILD_DIR := build
LIBFT_DIR := libs/libft
MLX42_DIR := libs/MLX42

LIBFT := $(LIBFT_DIR)/libft.a
MLX42 := $(MLX42_DIR)/build/libmlx42.a

CC := cc
CFLAGS :=	-Wall -Wextra \
			-Iinclude \
			-I$(LIBFT_DIR) \
			-I$(MLX42_DIR)/include/MLX42 \
			-g -fsanitize=address

SOURCES :=	main.c \
			\
			destroy.c \
			init_doors.c \
			create_images.c \
			init_player.c \
			init.c \
			\
			dda.c \
			find_hit_point.c \
			set_distance.c \
			set_end_point.c \
			set_hit_texture.c \
			\
			draw_map.c \
			draw_minimap.c \
			draw_player.c \
			draw_scene.c \
			\
			close_handler.c \
			handle_collisions.c \
			loop_handler.c \
			process_inputs.c \
			update_ui.c \
			update.c \
			\
			clear_image.c \
			clear_pixels.c \
			color.c \
			copy_pixels.c \
			fill.c \
			get_door.c \
			get_pixels.c \
			is_equal.c \
			is_valid_position.c \
			load_png.c \
			max.c \
			\
			delete_map.c \
			get_map.c \
			get_texture.c \
			input_validation_utils.c \
			is_enclosed.c \
			is_wall.c \
			load_map.c \
			map_validation.c \
			parse_colors.c \
			validate_file.c \
			valid_door.c \
			\
			delete_sprite.c \
			image_to_sprite.c \
			\
			transition_door.c \
			transition_player.c \
			update_door.c \
			update_player.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(MLX42) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX42) -ldl -lglfw -pthread -lm -o $(NAME)
	@printf "$(YELLOW)$@$(RESET) created.\n"

$(BUILD_DIR):
	@mkdir -p $@
	@echo "Compiling ..."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent
	@printf "$(YELLOW)$@$(RESET) created.\n"

$(MLX42):
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && $(MAKE) -C $(MLX42_DIR)/build -j4
	@printf "$(YELLOW)$@$(RESET) created.\n"

$(BUILD_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@rm -rf $(BUILD_DIR)
	@printf "$(RED)$(BUILD_DIR)/$(RESET) deleted.\n"
#	@rm -rf $(MLX42_DIR)/build
	@printf "$(RED)$(MLX42_DIR)/build/$(RESET) deleted.\n"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@printf "$(RED)$(LIBFT)$(RESET) deleted.\n"
	@rm -f $(NAME)
	@printf "$(RED)$(NAME)$(RESET) deleted.\n"

re: fclean $(NAME)
