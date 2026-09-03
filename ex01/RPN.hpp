#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN {
	private :
		RPN();
		RPN(RPN const & src);
		RPN		operateur=(RPN const & rhs);
		~RPN();
	public :
		int		evalutate(std::string const & expression);
};

#endif
