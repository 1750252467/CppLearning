#include <iostream>
using std::cout;
using std::endl;

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

int main(int argc,char ** argv)
{
    std::string initFileName = "log4cpp.conf";
    using namespace log4cpp;
    PropertyConfigurator::configure(initFileName);

    Category& root = Category::getRoot();

    Category& sub1 = 
        Category::getInstance(std::string("sub1"));

    Category& sub2 =
        Category::getInstance(std::string("sub1.sub2"));
	root.warn("Storm is coming");

	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

	sub1.info("All hatches closed");

	root.info("Ready for storm.");

	log4cpp::Category::shutdown();
    return 0;
}
