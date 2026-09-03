#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN {
	private :
		RPN();
		RPN(RPN const & src);
		RPN				operator=(RPN const & rhs);
		~RPN();
	public :
		static int		evaluate(std::string const & expression);
};

#endif
