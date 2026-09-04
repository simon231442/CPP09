NAME = btc

SOURCE = main.cpp \
		BitcoinExchange_constructor.cpp \
		BitcoinExchange_loadDatabase.cpp \
		BitcoinExchange_dateIsValid.cpp \
		BitcoinExchange_valueIsValid.cpp \
		BitcoinExchange_trim.cpp \
		BitcoinExchange_normalizeDate.cpp \
		BitcoinExchange_findClosestRate.cpp \
		BitcoinExchange_printConversion.cpp \
		BitcoinExchange_processInput.cpp

CCPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ_DIR = obj
OBJETS = $(SOURCE:%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJETS)
	$(CCPP) $(CPPFLAGS) $(OBJETS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CCPP) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
