#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


const Vector<String>& GetSoftBudgets() {
	static Vector<String> v;
	if (v.IsEmpty()) {
		v.Add("$100,000 - enough to cover the development and marketing costs for a small mobile game.");
		v.Add("$500,000 - a moderate budget for developing a virtual reality experience or a video editing software.");
		v.Add("$1 million - a budget that can cover the development of a simple app as well as marketing and advertising costs.");
		v.Add("$5 million - a larger budget for more complex software projects such as a multiplayer game or a productivity app.");
		v.Add("$10 million or more - a substantial budget for developing high-quality, multi-platform software projects with advanced features and functionality.");
		v.Add("Custom budgets - depending on the company's financial capabilities and goals, the budget size can vary greatly. Some companies may have a small budget of $50,000 while others may have a budget of over $20 million.");
		v.Add("Budget based on ROI - the budget can also be determined based on the expected ROI for a specific software project. For example, a company may allocate a budget of $500,000 for a software project that is expected to generate a high ROI, while only allocating $100,000 for a project with a lower expected ROI.");
	}
	return v;
}

const Vector<String>& GetSoftMarketTargets() {
	static Vector<String> v;
	if (v.IsEmpty()) {
		v.Add("Gamers: for a gaming software project such as a mobile game or PC game.");
		v.Add("Artists and creatives: for a software project that caters to the needs of graphic designers, photographers, or digital artists.");
		v.Add("Business professionals: for a productivity software project such as project management or time-tracking tools.");
		v.Add("Musicians: for a virtual instrument or music production software.");
		v.Add("Students: for educational apps or software projects.");
		v.Add("Children: for educational or entertainment software projects aimed at young audiences.");
		v.Add("Small business owners: for accounting or invoicing software.");
		v.Add("Health and fitness enthusiasts: for a fitness tracking or nutrition app.");
		v.Add("Gamers with disabilities: for an inclusive gaming software project.");
		v.Add("Specific industries: for software projects that cater to the specific needs of industries such as healthcare, finance, or real estate.");
		v.Add("Multi-lingual audience: for software projects with language options or aimed at non-English speaking markets.");
		v.Add("All-inclusive: for software projects with a broad target audience, such as social media platforms or communication tools.");
		v.Add("Niche - Musicians: Musicians with a niche interest in a specific genre or instrument.");
		v.Add("Niche - Parents: Parents of children with special needs for educational or therapeutic software.");
		v.Add("Niche - Freelancers: Freelancers or solopreneurs in a specific industry, such as freelance writers or graphic designers.");
		v.Add("Niche - E-sports players: E-sports players and enthusiasts for gaming software projects.");
		v.Add("Niche - Language learners: Language learners for language learning apps or software programs.");
		v.Add("Niche - Animal owners: Animal or pet owners for pet-care related software.");
		v.Add("Niche - Cyclists & runners: Cyclists or runners for fitness tracking software.");
		v.Add("Niche - Gardeners: Gardeners or DIY enthusiasts for gardening or home improvement software.");
		v.Add("Niche - Seniors: Seniors for technology or accessibility software.");
		v.Add("Niche - Meditation: Meditation or mindfulness practitioners for meditation or relaxation apps.");
		v.Add("Niche - Book lovers: Book or literature lovers for e-reading apps or book recommendation software.");
		v.Add("Niche - Cooks: Cooks or foodies for recipe management or cooking apps.");
		v.Add("Niche - Tourists: Tourists or travelers for travel planning or language translation software.");
		v.Add("Niche - Yoga: Yoga enthusiasts for yoga instruction or tracking apps.");
		v.Add("Niche - Remote workers: Remote workers for productivity or time-tracking software.");
		v.Add("Niche - Collectors: Collectors for inventory or organization software.");
		v.Add("Niche - Eco-friendly consumers: Eco-friendly consumers for sustainability or environmental impact tracking apps.");
		v.Add("Niche - Urban gardeners: Urban gardeners for urban gardening or plant care apps.");
		v.Add("Niche - Beauty enthusiasts: Make-up or beauty enthusiasts for make-up or beauty tutorial apps.");
		v.Add("Niche - Outdoor enthusiasts: Outdoor enthusiasts for hiking or camping planning and tracking software.");
		v.Add("Niche - Retirees: Retirees for retirement planning or senior living information software.");
		v.Add("Niche - University students: University students for study aids or productivity software.");
		v.Add("Niche - Home cooks: Home cooks for meal planning and recipe organization software.");
		v.Add("Niche - Disabled musicians: Musicians with certain physical disabilities for assistive music software.");
		v.Add("Niche - Art collectors: Art collectors or enthusiasts for art database or inventory software.");
		v.Add("Niche - Dietary needs: People with specific dietary needs for recipe management or restaurant finder apps.");
		v.Add("Niche - Teachers: Teachers or educators for lesson planning or grading software.");
		v.Add("Niche - Disabled cyclists: Cyclists or runners with certain physical disabilities for assistive sports tracking software.");
		v.Add("Niche - Beauty salon: Beauty salon or spa owners and professionals for scheduling or inventory software.");
		v.Add("Niche - Motorcyclists: Motorcyclists or car enthusiasts for vehicle maintenance or tracking software.");
		v.Add("Niche - ADHD: Parents of children with ADHD for time management or behavior tracking software.");
		v.Add("Niche - Wedding planners: Wedding planners or engaged couples for wedding planning and organization software.");
		v.Add("Niche - Fashion designers: Textile or fashion designers for fashion design or pattern-making software.");
		v.Add("Niche - Remote teams: Remote teams for team communication or project management software.");
		v.Add("Niche - Mental health: Mental health professionals for therapy or mental health tracking software.");
		v.Add("Niche - Independent musicians: Independent musicians or bands for music distribution and promotion software.");
		v.Add("Niche - Coin or stamp collectors: Coin or stamp collectors for inventory or valuation software.");
		v.Add("Niche - Vehicle collectors: Vehicle collectors or enthusiasts for classic car or motorcycle database software.");
		v.Add("Niche - Interior designers: Interior designers for interior design or visualization software.");
		v.Add("Niche - Fitness enthusiasts: Crossfit or fitness enthusiasts for workout tracking and planning apps.");
	}
	return v;
}


END_TEXTLIB_NAMESPACE
