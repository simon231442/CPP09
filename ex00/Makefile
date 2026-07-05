NAME = btc

################################################################################
#                               DIRECTORIES                                    #
################################################################################

OBJ_DIR = obj

################################################################################
#                                SOURCE FILES                                  #
################################################################################

SOURCE = BitcoinExchange_constructor.cpp BitcoinExchange_loadDatabase.cpp BitcoinExchange_dateIsValid.cpp

################################################################################
#                             COMPILER OPTIONS                                 #
################################################################################

CCPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 

OBJETS = $(SOURCE:%.cpp=$(OBJ_DIR)/%.o)

################################################################################
#                              TARGETS & RULES                                 #
################################################################################

all : $(NAME)

$(NAME) : $(OBJETS)
	$(CCPP) $(CPPFLAGS) $(OBJETS) -o $(NAME)

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(CCPP) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

