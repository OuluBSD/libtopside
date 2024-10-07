#include "ToolCore.h"


BEGIN_TEXTLIB_NAMESPACE



ColoredText SignificantPhrases[VOCABULARYTYPE_COUNT][SIGNIFICANT_PHRASE_COUNT] = {
	
	{
		{"soul", 255,255,255},
		{"love", 255,0,255},
		{"dream", 255,255,0},
		{"heart", 255,0,0},
		{"hope", 0,255,0},
		{"beauty", 255,195,145},
		{"journey", 145, 75, 255},
		{"peace", 50,205,50},
		{"whisper", 255,255,255},
		{"freedom", 0,255,255},
		{"embrace", 255,153,153},
		{"desire", 255,85,85},
		{"enchanted", 153,153,255},
		{"rain", 50,50,255},
		{"feel", 255,218,185},
		{"passion", 255,0,0},
		{"forever", 255,255,0},
		{"innocence", 255,255,255},
		{"promise", 255,165,0},
		{"belong", 255,165,255},
		{"truth", 0,0,255},
		{"wonder", 102,255,255},
		{"faith", 0,153,0},
		{"heaven", 204,255,255},
		{"light", 255,255,255},
		{"remember", 255,255,255},
		{"embrace", 255,153,153},
		{"adventure", 51,204,255},
		{"one", 255,204,204},
		{"star", 255,215,0},
		{"magic", 153,50,204},
		{"never", 255,255,255},
		{"together", 255,195,145},
		{"dance", 255,204,153},
		{"eternity", 255,255,0},
		{"release", 153,50,204},
		{"melody", 255,255,255},
		{"shine", 255,255,0},
		{"mystery", 153,204,255},
		{"wanderlust", 102,204,255},
		{"endless", 255,255,255},
		{"moment", 153,255,204},
		{"breathe", 178,255,255},
		{"song", 255,255,255},
		{"grace", 255,255,255},
		{"ocean", 0,204,255},
		{"sweet", 255,204,255},
		{"song", 255,255,255},
		{"wild", 255,153,153},
		{"eternal", 255,255,255},
		{"sun", 255,255,0},
		{"believe", 153,255,153},
		{"silence", 255,255,255},
		{"creation", 255,153,255},
		{"paradise", 255,255,255},
		{"miracle", 255,255,255},
		{"healing", 255,153,153},
		{"home", 255,215,0},
		{"infinity", 255,255,0},
		{"sunshine", 255,255,0},
		{"echo", 255,255,255},
		{"beauty", 255,195,145},
		{"mysterious", 153,153,255},
		{"breathe", 178,255,255},
		{"serenity", 102,153,255},
		{"pure", 255,255,255},
		{"wings", 102,204,255},
		{"echoes", 255,255,255},
		{"melancholy", 255,195,145},
		{"magic", 153,50,204},
		{"harmony", 255,255,0},
		{"beneath", 0,255,255},
		{"magical", 153,102,255},
		{"silver", 192,192,192},
		{"serenade", 255,255,255},
		{"inspire", 255,204,204},
		{"oasis", 255,215,0},
		{"shimmer", 255,215,0},
		{"exploration", 0,204,204},
		{"sparkle", 255,255,0},
		{"fragile", 255,195,145},
		{"bliss", 255,255,255},
		{"paradigm", 153,0,0},
		{"journeys", 145, 75, 255},
		{"wonderment", 51,204,255},
		{"graceful", 255,255,255},
		{"radiant", 255,255,0},
		{"heavens", 51,204,255},
		{"gratitude", 255,255,255},
		{"moons", 145, 75, 255},
		{"dancing", 255,204,153},
		{"starstruck", 255,153,153},
		{"breathing", 178,255,255},
		{"innocently", 255,255,255},
		{"whispers", 255,255,255},
		{"abandonment", 255,255,255},
		{"sparkling", 255,255,0},
		{"glistening", 255,255,255},
		{"warrior", 51,153,255},
		{"eternally", 255,153,153},
	}, {{"tranquility", 0,128,0},
		{"serenity", 0,192,192},
		{"azure", 0,128,255},
		{"oceanic", 0,64,128},
		{"soothing", 0,192,128},
		{"starry", 0,128,128},
		{"turquoise", 0,128,128},
		{"lush", 0,255,0},
		{"sapphire", 0,0,128},
		{"emerald", 0,192,0},
		{"scenic", 0,128,0},
		{"harmony", 0,128,0},
		{"calming", 0,160,128},
		{"serene", 0,128,128},
		{"jade", 0,128,64},
		{"blissful", 0,192,128},
		{"aquatic", 0,0,128},
		{"tranquil", 0,192,192},
		{"peaceful", 0,128,192},
		{"verdant", 0,128,128},
		{"seabreeze", 0,64,128},
		{"galaxy", 0,0,128},
		{"resonant", 0,128,64},
		{"relaxing", 0,160,128},
		{"mellow", 0,192,192},
		{"invigorating", 0,255,255},
		{"refreshing", 0,192,192},
		{"watercolor", 0,128,128},
		{"paradise", 0,64,192},
		{"satisfying", 0,128,160},
		{"splendid", 0,128,128},
		{"aquamarine", 0,128,192},
		{"rejuvenate", 0,255,192},
		{"tranquility", 0,192,128},
		{"gentle", 0,160,192},
		{"delicate", 0,192,160},
		{"gleaming", 0,128,255},
		{"ripple", 0,64,128},
		{"glimmer", 0,64,192},
		{"vibrant", 0,255,128},
		{"breeze", 0,128,64},
		{"nature", 0,128,0},
		{"floral", 0,128,128},
		{"balance", 0,160,128},
		{"dive", 0,0,128},
		{"nature", 0,128,0},
		{"nurture", 0,128,64},
		{"lullaby", 0,192,192},
		{"oasis", 0,128,255},
		{"lively", 0,255,128},
		{"luminous", 255,192,128},
		{"radiant", 255,128,64},
		{"vibrant", 255,192,0},
		{"fiery", 255,64,0},
		{"passionate", 255,64,64},
		{"flamboyant", 255,128,0},
		{"invigorating", 255,128,0},
		{"enthralling", 255,0,0},
		{"mesmerizing", 255,128,0},
		{"captivating", 255,128,0},
		{"dazzling", 255,128,0},
		{"rousing", 255,64,0},
		{"enthusiastic", 255,255,0},
		{"exhilarating", 255,128,0},
		{"enchanting", 255,64,0},
		{"blazing", 255,0,0},
		{"fervent", 255,64,64},
		{"spirited", 255,192,0},
		{"inspiring", 255,255,0},
		{"thrilling", 255,0,0},
		{"dynamic", 255,255,0},
		{"exuberant", 255,128,0},
		{"vivid", 255,128,0},
		{"electrifying", 255,255,0},
		{"passion", 255,0,0},
		{"desire", 255,160,0},
		{"rousing", 255,128,0},
		{"intense", 255,64,0},
		{"irresistible", 255,128,0},
		{"effervescent", 255,192,0},
		{"flaming", 255,64,0},
		{"explosive", 255,0,0},
		{"seductive", 255,160,0},
		{"glowing", 255,192,0},
		{"stimulating", 255,192,0},
		{"passionate", 255,128,0},
		{"vibrant", 255,192,0},
		{"exciting", 255,255,0},
		{"zealous", 255,160,0},
		{"passion-filled", 255,0,0},
		{"intoxicating", 255,128,0},
		{"alluring", 255,64,0},
		{"persuasive", 255,160,0},
		{"mesmerizing", 255,192,0},
		{"sizzling", 255,0,0},
		{"enticing", 255,192,0},
		{"volcanic", 255,0,0},
		{"captivating", 255,128,0},
		{"invigorating", 255,128,0},
		{"pleasing", 255,192,0},
	},{	{"jealousy", 0,128,192},
		{"envy", 0,255,128},
		{"bitterness", 0,192,128},
		{"coldness", 0,128,255},
		{"apathy", 0,64,128},
		{"loneliness", 0,128,0},
		{"sorrow", 0,64,0},
		{"melancholy", 0,128,0},
		{"depression", 0,192,128},
		{"despair", 0,128,192},
		{"grief", 0,128,128},
		{"betrayal", 0,192,0},
		{"disillusionment", 0,128,64},
		{"stinginess", 0,192,64},
		{"cynicism", 0,192,128},
		{"pride", 0,128,64},
		{"ambition", 0,255,64},
		{"greed", 0,192,0},
		{"materialism", 0,128,128},
		{"superficiality", 0,128,64},
		{"dramatic", 0,255,128},
		{"manipulative", 0,128,255},
		{"demanding", 0,0,128},
		{"control", 0,192,192},
		{"maneuver", 0,128,0},
		{"callous", 0,255,0},
		{"secrets", 0,128,0},
		{"depths", 0,64,128},
		{"underhanded", 0,128,192},
		{"bruises", 0,128,255},
		{"cuts", 0,128,192},
		{"lies", 0,128,255},
		{"greed", 0,255,128},
		{"gluttony", 0,128,192},
		{"lust", 0,192,128},
		{"wrath", 0,128,192},
		{"sloth", 0,128,128},
		{"apathy", 0,192,192},
		{"indolence", 0,128,192},
		{"anxiety", 0,255,128},
		{"fatigue", 0,5,128},
		{"sadness", 0,64,128},
		{"embarrassment", 0,128,0},
		{"guilt", 0,5,0},
		{"shame", 0,192,192},
		{"loneliness", 0,128,0},
		{"regret", 0,64,128},
		{"despair", 0,255,128},
		{"fear", 0,128,0},
		{"disappointment", 0,5,128},
		{"rage", 255,0,0},
		{"burning", 255,80,0},
		{"temper", 255,16,0},
		{"violence", 255,0,64},
		{"fire", 255,0,0},
		{"captivated", 255,160,0},
		{"fury", 255,32,0},
		{"jealousy", 255,128,0},
		{"passion", 255,0,0},
		{"anguish", 255,0,0},
		{"demanding", 255,255,0},
		{"frenzy", 255,64,0},
		{"sudden", 255,0,0},
		{"impulsive", 255,32,0},
		{"arrogant", 255,80,0},
		{"excited", 255,160,0},
		{"rash", 255,0,0},
		{"reckless", 255,64,0},
		{"uncontrolled", 255,64,0},
		{"intense", 255,0,0},
		{"frustrated", 255,128,0},
		{"outburst", 255,16,0},
		{"thunder", 255,128,0},
		{"yell", 255,16,0},
		{"explosive", 255,0,0},
		{"stress", 255,96,0},
		{"tantrum", 255,16,0},
		{"tantrum", 255,64,0},
		{"stormy", 255,32,0},
		{"burst", 255,0,0},
		{"uproar", 255,96,0},
		{"struggle", 255,128,0},
		{"wailing", 255,0,0},
		{"eruption", 255,0,0},
		{"worrying", 255,144,0},
		{"concern", 255,128,0},
		{"anxious", 255,160,0},
		{"wrath", 255,64,0},
		{"boisterous", 255,0,0},
		{"vexing", 255,144,0},
		{"impatient", 255,160,0},
		{"discomfort", 255,96,0},
		{"enraged", 255,0,0},
		{"jeer", 255,128,0},
		{"anguished", 255,0,0},
		{"dread", 255,32,0},
		{"outcry", 255,0,0},
		{"pouting", 255,96,0},
		{"yelp", 255,0,64},
		{"brash", 255,80,0}
	},
	
	
	
	// Phrases
	{
		{"heart on fire", 255,0,0},
		{"dancing in the dark", 0,0,0},
		{"searching for meaning", 255,255,0},
		{"breaking the chains", 51,51,51},
		{"ride or die", 102,0,102},
		{"living in the moment", 255,128,0},
		{"chasing dreams", 51,153,255},
		{"soul on fire", 255,0,0},
		{"love and pain", 255,204,204},
		{"fighting for my voice", 76,0,153},
		{"rise from the ashes", 255,153,51},
		{"never giving up", 255,255,255},
		{"finding my way", 0,102,102},
		{"lost and found", 0,0,204},
		{"breaking free", 255,102,102},
		{"wild and free", 0,153,0},
		{"beating to our own drum", 255,51,153},
		{"writing our own story", 255,255,102},
		{"holding onto hope", 255,255,0},
		{"embracing imperfection", 204,204,204},
		{"never looking back", 0,0,0},
		{"defying the odds", 255,0,0},
		{"daring to be different", 255,0,255},
		{"embracing the unknown", 0,0,255},
		{"trusting the journey", 0,255,0},
		{"raw emotion", 255,0,0},
		{"unleashing passion", 255,0,204},
		{"living without regret", 0,102,0},
		{"embodying strength and vulnerability", 153,51,51},
		{"facing fears head on", 204,0,102},
		{"authentic self-expression", 102,0,204},
		{"finding beauty in the chaos", 204,204,0},
		{"dreaming in color", 0,153,153},
		{"living in the present", 0,255,255},
		{"creating our own destiny", 153,153,255},
		{"endless possibilities", 255,204,0},
		{"escaping reality", 102,102,102},
		{"light in the darkness", 255,255,255},
		{"conquering inner demons", 102,0,0},
		{"never backing down", 204,0,0},
		{"fearless and fierce", 255,51,51},
		{"exploring uncharted territory", 255,255,0},
		{"redefining success", 51,255,153},
		{"living fearlessly", 255,255,255},
		{"embodying resilience", 102,102,102},
		{"breaking the mold", 255,102,0},
		{"embracing individuality", 0,0,255},
		{"overflowing with love", 255,255,204},
		{"finding strength in vulnerability", 255,102,102},
		{"navigating the unknown", 102,255,102},
		{"striving for greatness", 204,0,204},
		{"never compromising integrity", 0,204,0},
		{"embracing the journey", 255,255,153},
		{"defiant and determined", 255, 0,102},
		{"carving our own path", 255,255,255},
		{"living with passion", 255,204,153},
		{"healing through music", 255,153,0},
		{"confronting our demons", 102,51,0},
		{"embodying authenticity", 255,102,102},
		{"embracing flaws", 255,153,153},
		{"rising from the ashes", 255,51,0},
		{"intertwining passion and purpose", 255, 0,255},
		{"never conforming", 255,51,255},
		{"blazing our own trail", 255,255,255},
		{"embracing change", 0,255,0},
		{"daring to dream", 204,153,255},
		{"endless possibilities", 255,204,204},
		{"embracing the chaos", 255,204,255},
		{"conquering self doubt", 204,255,153},
		{"fueling the fire within", 204,153,0},
		{"overcoming obstacles", 255,255,102},
		{"embracing the unknown", 255,0,153},
		{"embodying grace and strength", 255,0,204},
		{"breaking barriers", 255,51,153},
		{"finding solace in music", 255,255,154},
		{"unapologetically oneself", 153,153,153},
		{"pushing past limitations", 255,255,0},
		{"living with passion and purpose", 255,204,204},
		{"embracing individualism", 255,255,255},
		{"defying expectations", 0,255,153},
		{"navigating through pain", 153,153,255},
		{"rebelling against conformity", 204,204,153},
		{"embracing vulnerability", 255,51,255},
		{"releasing inner demons", 255,0,153},
		{"unleashing creativity", 153,51,255},
		{"never losing hope", 102,102,102},
		{"dancing through the storm", 0,255,255},
		{"living out loud", 255,0,0},
		{"redefining beauty", 153,51,153},
		{"defining our own truth", 153,0,204},
		{"embracing the journey within", 255,255,0},
		{"learning to love ourselves", 255,255,255},
		{"enduring through hardship", 102,0,51},
		{"chasing our wildest dreams", 0,0,0},
		{"striving for authenticity", 51,0,0},
		{"building ourselves up", 204,204,102},
		{"breaking through walls", 204,102,0},
		{"carving our own destiny", 102,0,255},
		{"embracing the present", 255,0,0},
		{"finding strength in vulnerability", 255,204,204},
	},{
		{"feeling blue and green with joy", 0,255,128},
		{"blue eyes smiling, surrounded by green laughter", 0,128,192},
		{"like a blue butterfly, free and flying, among green leaves", 0,192,255},
		{"painting my world in shades of blue and green, full of possibilities", 64,128,192},
		{"green fields and blue skies, a perfect day to explore", 0,255,192},
		{"blue and green, the colors of peace, love, and harmony", 64,192,128},
		{"feeling blue and green, like the ocean and sky, never ending", 0,192,192},
		{"in a sea of blue and green, I find my inner peace", 0,64,128},
		{"emerald city, blue skies above, a magical place of wonder", 0,160,128},
		{"the bluish-green hues of nature, a soothing symphony", 0,96,64},
		{"like a chameleon, I can feel blue and green at the same time", 0,255,64},
		{"blueberry fields, green apple orchards, a feast for the senses", 64,128,0},
		{"blue notes, draped in a green velvet dress, a classy combination", 64,64,128},
		{"in a blue funk, surrounded by the calming shades of green", 0,64,0},
		{"the blues and greens of life, contrasting yet complimentary", 0,0,64},
		{"in the midst of blue and green, finding my center and balance", 64,64,0},
		{"beneath the blue sky, a green meadow awaits, an invitation to play", 0,192,192},
		{"feeling blue and green, like a work of art, full of contrasts", 128,128,128},
		{"two peas in a pod, one blue, one green, a perfect pair", 0,128,128},
		{"like a peacock, showing off my blue and green hues, proud and confident", 0,64,64},
		{"under the blue moon, the green fields come alive, a magical night", 0,192,255},
		{"the deep blue sea, met with the lush green coast, a tranquil escape", 0,64,160},
		{"feeling blue and green, embracing the yin and yang, a balanced and whole self", 128,64,0},
		{"the rolling blue waves, surrounded by the vibrant shades of green, a breathtaking sight", 0,32,96},
		{"blueprints for the future, inspired by the green world, a bright and sustainable future", 0,64,255},
		{"green grass and blue skies, the perfect backdrop for cherished memories", 0,192,64},
		{"tears of blue, leaves of green, a bittersweet goodbye, full of love and gratitude", 0,192,255},
		{"the blue-green hues of a sun-soaked day, memories to last a lifetime, a beautiful life", 128,64,255},
		{"like a turquoise gemstone, a subtle blend of blue and green, unique and precious", 0,128,192},
		{"feeling blue and green, like a flower in a bed of grass, strong and resilient", 0,255,160},
		{"blue skies, green fields, and a heart full of hope and dreams, the perfect recipe for happiness", 0,255,128},
		{"painting the world in shades of blue and green, a colorful and vibrant existence", 64,128,192},
		{"the colors of peace, love, and harmony, blue and green, a powerful combination", 64,192,128},
		{"feeling blue and green, like the ocean and sky, endless possibilities and opportunities", 0,192,192},
		{"in a sea of blue and green, finding solace and serenity, a tranquil sanctuary", 0,64,128},
		{"emerald city, blue skies above, a magical place of wonder, full of joy and surprises", 0,160,128},
		{"green fields and blue skies, a perfect day to explore, full of adventure and excitement", 0,255,192},
		{"the blues and greens of nature, a beautiful symphony, full of life and harmony", 0,96,64},
		{"in the midst of blue and green, finding my center and balance, an inner peace and calm", 64,64,0},
		{"beneath the blue sky, a green meadow awaits, an invitation to play and be carefree", 0,192,192},
		{"two peas in a pod, one blue, one green, a perfect match, full of love and understanding", 0,128,128},
		{"like a peacock, showing off my blue and green hues, confident and full of self-love", 0,64,64},
		{"under the blue moon, the green fields come alive, a magical night, full of love and possibilities", 0,192,255},
		{"the deep blue waters, met with the lush green coast, a tranquil escape, a peaceful haven", 0,64,160},
		{"painting my world in shades of blue and green, a colorful masterpiece, full of joy and passion", 64,128,192},
		{"blueprints for the future, inspired by the green world, a bright and sustainable future, full of hope and dreams", 0,64,255},
		{"green grass and blue skies, the perfect backdrop for cherished memories, a heart full of gratitude and love", 0,192,64},
		{"tears of blue, leaves of green, a bittersweet goodbye, full of love and appreciation, for a life well-lived", 0,192,255},
		{"the blue-green hues of a sun-soaked day, memories to last a lifetime, a beautiful life, full of blessings and fulfillment", 128,64,255},
		{"like a turquoise gemstone, a subtle blend of blue and green, unique and precious, full of inner strength and resilience", 0,128,192},
		{"feeling on top of the world, with a fiery heart", 255,0,0},
		{"radiating golden vibes, with a passionate soul", 255,128,0},
		{"like a blazing fire, my spirit burns bright", 255,64,0},
		{"feeling the warmth of the sun, and the fire within", 255,192,0},
		{"pumping with adrenaline, with a bright red heart", 255,0,128},
		{"like a red rose, blooming with love and passion", 255,0,64},
		{"feeling bold and confident, with a fiery orange glow", 255,128,64},
		{"like a sunset on a summer evening, my heart is painted with shades of orange", 255,128,128},
		{"ignited by passion, with a flaming red heart", 255,0,192},
		{"embracing my adventurous spirit, with a fiery soul", 255,64,64},
		{"like a rising sun, my heart glows with shades of orange and yellow", 255,192,64},
		{"feeling electrifying energy, with a vibrant red heart", 255,0,255},
		{"like a crackling fire, my heart burns with passion and desire", 255,64,128},
		{"radiating warmth and joy, with a golden heart", 255,192,128},
		{"like a burst of sunshine, my heart beams with shades of yellow and orange", 255,255,0},
		{"feeling alive and vibrant, with a heart of fiery red", 255,0,64},
		{"like a summer day, my heart radiates with shades of yellow and orange", 255,192,0},
		{"in a world of chaos, my heart remains steady and strong, like a red beacon", 255,0,128},
		{"like a flickering flame, my heart glows with passion and determination", 255,128,0},
		{"embracing my inner fire, with a heart of deep red", 255,64,0},
		{"like a field of wildflowers, my soul is painted with shades of orange and yellow", 255,192,192},
		{"feeling the warmth of love, with a red heart full of emotions", 255,0,64},
		{"like a ripe fruit, my heart is filled with warm shades of orange and red", 255,128,64},
		{"embracing my vibrant energy, with a fiery heart", 255,64,192},
		{"like a blazing sun, radiating with warmth and vitality, my heart beats strong", 255,192,255},
		{"feeling the fire of passion, with a heart of deep red and orange", 255,0,0},
		{"like a sunset on the horizon, my heart paints the sky with shades of orange and red", 255,128,128},
		{"in a world of darkness, my heart shines like a bright yellow sun", 255,255,128},
		{"like a fiery comet, my heart burns with passion and purpose", 255,64,64},
		{"breathing in the warmth of the sun, feeling alive with a heart of fiery red", 255,0,128},
		{"like a field of wildflowers, my soul is painted with shades of yellow and orange", 255,255,64},
		{"in a world of chaos and turmoil, my heart remains steady and strong with shades of red and orange", 255,128,0},
		{"like a crackling fire, my heart burns with passion and desire in every beat", 255,0,192},
		{"breathing in the warm summer air, feeling the joy and warmth of my golden heart", 255,128,192},
		{"like a setting sun, my heart glows with shades of orange and red, radiating warmth and love", 255,192,64},
		{"in a sea of black and white, my heart is painted with vibrant shades of red, orange, and yellow", 255,0,0},
		{"like a flickering flame, my passion and energy shine through with a heart of fiery red", 255,128,64},
		{"breathing in the sunrise, feeling the energy and vitality of my passionate, yellow heart", 255,255,0},
		{"like a burst of sunshine, my heart radiates joy and warmth with shades of orange and yellow", 255,192,0},
		{"in a world of chaos, my heart remains steady and strong like a vibrant, red beacon", 255,0,128},
		{"like a ripe fruit, my heart is filled with warm shades of yellow and orange, ready to be savored", 255,128,255},
		{"embracing my inner fire, with a heart of deep red and orange, full of passion and strength", 255,64,0},
		{"like a field of wildflowers, my soul is painted with vibrant shades of orange and yellow, bursting with life", 255,192,128},
		{"in a world of darkness, my heart shines like a bright ray of yellow sun, bringing warmth and light to all", 255,255,128},
		{"like a fiery comet, my heart burns with passion and purpose in every step I take", 255,0,64},
		{"embracing my vibrant energy, with a heart of bright red and warm shades of orange", 255,64,192},
		{"breathing in the warmth of love, feeling the fiery passion and deep emotions of my heart", 255,128,192},
		{"like a blazing sun, radiating with warmth and vitality, my heart beats strong with shades of red and yellow", 255,255,0},
		{"in a world of chaos and turmoil, my heart remains steady and strong, burning with a fiery orange glow", 255,128,0},
		{"like a field of wildflowers, my soul is painted with vivid shades of red, orange, and yellow, each petal glowing with life and beauty", 255,192,192}
	},{	{"green with envy and blue with sadness", 0,64,192},
		{"feeling blue and green, lost and confused", 96,0,0},
		{"the grass is greener on the other side, but the sky is always bluer", 128,0,64},
		{"stuck in a blue and green rut, longing for change", 128,96,0},
		{"the cold blue of loneliness, and the bitter green of jealousy", 64,128,192},
		{"blue eyes, green with jealousy, ruining relationships", 255,0,128},
		{"all alone in a blue world, surrounded by green-eyed friends", 0,255,96},
		{"a greyish-blue life, with just specks of green happiness", 64,64,64},
		{"feeling blue and green, like a faded painting, once full of life", 128,128,64},
		{"the monotony of life, painted in shades of blue and green", 96,96,96},
		{"the blues and greens of envy, creating chaos and destruction", 192,192,0},
		{"the dark blue of depression, surrounded by a sea of green envy", 0,0,64},
		{"like a blue and green kaleidoscope, my emotions are constantly shifting", 96,96,191},
		{"blue and green, like fire and water, constantly battling within me", 128,0,0},
		{"the green haze of jealousy, blurring my true blue feelings", 160,128,0},
		{"feeling blue and green, committing to nothing but self-destruction", 64,128,191},
		{"like a stormy ocean, my emotions are a tumultuous mix of blue and green", 0,191,255},
		{"drowning in a sea of blue and green, unable to escape the negativity", 127,127,63},
		{"the grass is greener on the other side, but the sky is always bluer, mocking me", 192,192,191},
		{"a blue and green nightmare, never-ending and suffocating", 127,63,0},
		{"the blue and green traps of jealousy and comparison, stopping me from moving forward", 255,127,0},
		{"like a blue and green poison, spreading and destroying everything in its path", 191,63,0},
		{"the blue abyss of depression, surrounded by the green walls of fear", 64,191,0},
		{"feeling blue and green, like a broken kaleidoscope, shattered into a million pieces", 63,63,63},
		{"blue and green, like quicksand, pulling me deeper into the negativity", 0,63,127},
		{"under a dark blue cloud, with a hint of green, drowning in self-pity", 0,127,255},
		{"like a green-eyed monster, the blue of sadness consumes me", 159,159,159},
		{"feeling blue and green, unable to find a balance, constantly falling to one side", 191,63,127},
		{"the greens and blues of regret, permeating every aspect of my life", 191,159,0},
		{"like a blue and green fog, clouding my judgement and poisoning my thoughts", 191,127,63},
		{"under a blue and green spell, unable to break free from its grasp", 63,191,127},
		{"the bright blue of hope, dimmed by the deep green of jealousy", 255,63,159},
		{"like a blue and green ocean, crashing against the shores of my mind", 0,127,191},
		{"the never-ending cycle of envy and depression, painted in shades of blue and green", 255,63,0},
		{"like a blue and green tornado, destroying everything in its path", 63,191,191},
		{"feeling blue and green, like a puppet controlled by the hands of jealousy and insecurity", 159,159,191},
		{"like a blue and green maze, constantly losing myself in the negativity", 127,255,191},
		{"the dark blue of self-doubt, enveloped in the sickly green of envy", 63,191,191},
		{"like a blue and green poison, slowly seeping into my veins and corrupting my mind", 159,191,159},
		{"the overwhelming blue of sadness, highlighted by the bitter green of envy", 127,255,127},
		{"in a sea of blue and green, drowning in my own negative thoughts", 63,255,0},
		{"the endless shades of blue and green, a constant reminder of my discontentment", 191,159,159},
		{"like a blue and green storm, raging inside of me and leaving destruction in its wake", 63,255,255},
		{"the blue of melancholy, mixed with the green of resentment, a toxic combination", 159,255,255},
		{"like a blue and green mirage, luring me into a false sense of security", 63,159,127},
		{"feeling blue and green, like an out-of-tune symphony, creating dissonance in my life", 127,191,159},
		{"trapped in a blue and green prison, unable to break free from the shackles of negativity", 159,159,191},
		{"like a blue and green venom, infecting my thoughts and poisoning my soul", 255,127,191},
		{"the dark blue of depression, hidden behind a facade of green envy", 63,63,191},
		{"like a blue and green cancer, slowly spreading and consuming me from within", 127,127,191},
		{"seeing red with anger and envy",255,0,0},
		{"feeling the heat of a fiery temper", 255,128,0},
		{"painting the town red, with shades of bitterness", 255,0,128},
		{"seeing everything through rose-colored glasses, until reality hits", 255,128,192},
		{"burning with jealousy, turning orange with rage", 255,64,0},
		{"in a yellowish mood, feeling sour and bitter", 255,255,0},
		{"painting the walls with shades of regret and resentment", 255,64,64},
		{"seeing red, reacting in a destructive manner", 255,0,0},
		{"walking on thin red lines, struggling to keep composure", 255,0,64},
		{"feeling blue and green, but turning red with embarrassment", 255,64,64},
		{"in a fiery mood, seeing red and acting recklessly", 255,96,0},
		{"feeling hot-tempered and red in the face", 255,64,0},
		{"seeing orange with frustration and impatience", 255,128,64},
		{"caught in a web of lies, turning purple with anger", 128,0,255},
		{"feeling yellow and cowardly, afraid to face the truth", 255,255,128},
		{"battling a red tide of negative thoughts", 255,0,64},
		{"turning red with embarrassment, trying to hide from the spotlight", 255,64,0},
		{"caught red-handed, admitting to guilt", 255,0,64},
		{"feeling yellow and defeated, giving up on hope", 255,255,0},
		{"seeing red with jealousy, turning green with envy", 255,0,0},
		{"in the midst of a red storm, unable to see clearly", 255,0,128},
		{"feeling red with anger, blue with sadness", 255,0,0},
		{"in a black and white world, painted with shades of red and orange", 128,128,0},
		{"feeling the burn of a red-hot temper", 255,64,0},
		{"in a deep red mood, seeing everything in a dark light", 128,0,64},
		{"seeing shades of red and orange in a world that was once bright", 255,64,0},
		{"in a red state of mind, seeing the worst in everyone", 255,0,0},
		{"painting the walls with shades of anger and resentment", 255,0,0},
		{"seeing red and reacting impulsively", 255,0,64},
		{"feeling yellow and cowardly, unable to face the truth", 255,255,0},
		{"flying off the handle, turning red with rage", 255,0,0},
		{"in a dark red mood, drowning in a sea of negativity", 128,0,0},
		{"seeing everything through a red haze, losing control", 255,0,0},
		{"the red flags were there, but I chose to ignore them", 255,64,0},
		{"feeling truthfully red, unable to hide behind a facade", 255,0,0},
		{"seeing red and feeling an intense burning inside", 255,0,0},
		{"in the heat of the moment, seeing red and acting impulsively", 255,0,64},
		{"feeling red and hot with anger and frustration", 255,0,0},
		{"in a red and orange mood, unable to see the beauty in life", 255,64,0},
		{"burning bridges, turning orange and red with regret", 255,64,0},
		{"in a fiery state of mind, seeing everything in shades of red and orange", 255,96,0},
		{"in the red zone, unable to see beyond my own emotions", 255,0,0},
		{"caught in a spiral of negativity, seeing everything in shades of red", 255,64,64},
		{"seeing red with intense fury, unable to control my actions", 255,0,0},
		{"feeling the weight of the world, a heavy burden of red and orange", 255,0,64},
		{"in a red mood, unable to find peace in a sea of chaos", 255,0,0},
		{"seeing shades of red and orange in a world that was once bright", 255,64,64},
		{"in a state of red, unable to find forgiveness and peace", 255,0,0},
		{"feeling a surge of red, unable to contain my emotions", 255,0,0},
		{"in a heated argument, seeing red and acting impulsively", 255,0,64}
	}
};





void rgb_to_hsv(float r, float g, float b, float& h, float& s, float& v) {
	// R, G, B values are divided by 255
	// to change the range from 0..255 to 0..1:
	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	float cmax = max(r, g, b); // maximum of r, g, b
	float cmin = min(r, g, b); // minimum of r, g, b
	float diff = cmax-cmin; // diff of cmax and cmin.
	if (cmax == cmin)
	  h = 0;
	else if (cmax == r)
	  h = fmod((60 * ((g - b) / diff) + 360), 360.0f);
	else if (cmax == g)
	  h = fmod((60 * ((b - r) / diff) + 120), 360.0f);
	else if (cmax == b)
	  h = fmod((60 * ((r - g) / diff) + 240), 360.0f);
	// if cmax equal zero
	  if (cmax == 0)
	     s = 0;
	  else
	     s = (diff / cmax);// * 100;
	// compute v
	v = cmax;// * 100;
}

int GetColorDistance(const Color& a, const Color& b) {
	float h0, s0, v0;
	float h1, s1, v1;
	rgb_to_hsv((float)a.GetR(), (float)a.GetG(), (float)a.GetB(), h0, s0, v0);
	rgb_to_hsv((float)b.GetR(), (float)b.GetG(), (float)b.GetB(), h1, s1, v1);
	
	float dh = min(fabs(h1-h0), 360.f-fabs(h1-h0)) / 180.0f;
	float ds = fabs(s1-s0);
	float dv = fabs(v1-v0) / 255.0f;
	float distance = sqrtf(dh*dh+ds*ds+dv*dv);
	return (int)(distance * 10000);
}


bool TextColorDistanceSorter::operator()(const int& ai, const int& bi) const {
	Color a, b;
	a = (*clr)[ai];
	b = (*clr)[bi];
	int dist0 = GetColorDistance(a, cmp);
	int dist1 = GetColorDistance(b, cmp);
	return dist0 < dist1;
}

void TextColorDistanceSorter::Sort() {
	ASSERT(str && clr && str->GetCount() == clr->GetCount());
	Vector<int> idx;
	for(int i = 0; i < str->GetCount(); i++)
		idx << i;
	UPP::Sort(idx, *this);
	
	Vector<String> new_str;
	Vector<Color> new_clr;
	new_str.Reserve(idx.GetCount());
	new_clr.Reserve(idx.GetCount());
	for (int i : idx) {
		new_str << (*str)[i];
		new_clr << (*clr)[i];
	}
	Swap(*str, new_str);
	Swap(*clr, new_clr);
}





const VectorMap<String,Color>& GetWordgroupColors() {
	static VectorMap<String,Color> list;
	if (list.GetCount()) return list;
	list.Add("pronouns", Color(204, 153, 255));
	list.Add("pronoun", Color(204, 153, 255));
	list.Add("noun", Color(150, 200, 100));
	list.Add("adjective", Color(255, 255, 0));
	list.Add("preposition", Color(100, 100, 100));
	list.Add("conjunction", Color(0, 0, 255));
	list.Add("verb", Color(255, 0, 0));
	list.Add("adverb", Color(0, 255, 0));
	list.Add("interjection", Color(255, 140, 0));
	list.Add("numbers", Color(255, 165, 0));
	list.Add("adverbial phrases", Color(255, 105, 180));
	list.Add("contractions", Color(214, 193, 255));
	list.Add("auxiliary verbs", Color(0, 128, 128));
	list.Add("relative pronouns", Color(0, 100, 0));
	list.Add("future tense verbs", Color(197, 179, 88));
	list.Add("past tense verbs", Color(255, 192, 203));
	list.Add("modal verbs", Color(240, 248, 255));
	list.Add("repetitive phrases", Color(100, 149, 237));
	list.Add("metaphors", Color(221, 160, 221));
	list.Add("hyperbole", Color(255, 255, 224));
	list.Add("assonance", Color(255, 182, 193));
	list.Add("consonance", Color(192, 192, 192));
	list.Add("alliteration", Color(255, 20, 147));
	list.Add("rhyming words", Color(119, 136, 153));
	list.Add("imperative verbs", Color(186, 85, 211));
	list.Add("exclamations", Color(255, 69, 0));
	list.Add("possessive adjectives", Color(222, 184, 135));
	list.Add("articles", Color(65, 105, 225));
	list.Add("personal pronouns", Color(0, 128, 0));
	list.Add("possessive determiners", Color(255, 0, 255));
	list.Add("active voice", Color(255, 0, 255));
	list.Add("repeated words", Color(0, 255, 0));
	list.Add("repetition", Color(0, 255, 0));
	list.Add("tone", Color(255, 69, 0));
	list.Add("mood", Color(255, 255, 0));
	list.Add("extended simile", Color(135, 206, 250));
	list.Add("irony", Color(250, 128, 114));
	list.Add("emotional words", Color(255, 223, 56));
	list.Add("strong verbs", Color(173, 216, 230));
	list.Add("emotive language", Color(255, 127, 80));
	list.Add("words that depict movement", Color(144, 238, 144));
	list.Add("descriptive words", Color(238, 130, 238));
	list.Add("words with multiple meanings", Color(173, 255, 47));
	list.Add("concern", Color(128, 0, 128));
	list.Add("pain", Color(139, 0, 0));
	list.Add("possessive pronouns", Color(255, 99, 71));
	list.Add("comparative adjectives", Color(107, 142, 35));
	list.Add("superlative adjectives", Color(102, 205, 170));
	list.Add("direct speech", Color(0, 0, 128));
	list.Add("indirect speech", Color(128, 0, 0));
	list.Add("personification", Color(255, 20, 147));
	list.Add("onomatopoeia", Color(0, 100, 0));
	list.Add("auxiliary adjectives", Color(255, 192, 203));
	list.Add("question words", Color(0, 191, 255));
	list.Add("passive voice", Color(255, 255, 0));
	list.Add("compound words", Color(245, 222, 179));
	list.Add("contradictions", Color(255, 105, 180));
	list.Add("extended metaphor", Color(112, 128, 144));
	list.Add("rhetorical question", Color(128, 0, 128));
	list.Add("symbolism", Color(173, 216, 230));
	list.Add("dramatic endings", Color(175, 0, 0));
	list.Add("repeated chorus", Color(0, 255, 255));
	list.Add("metaphorical simile", Color(250, 128, 114));
	list.Add("weak verbs", Color(255, 218, 185));
	list.Add("onomatopoeic words", Color(152, 251, 152));
	list.Add("symbolic words", Color(0, 191, 255));
	list.Add("insanity", Color(0, 0, 128));
	list.Add("preposition", Color(100, 100, 100));
	list.Add("conjunction", Color(0, 0, 255));
	list.Add("verb", Color(255, 0, 0));
	list.Add("adverb", Color(0, 255, 0));
	list.Add("interjection", Color(255, 140, 0));
	list.Add("tone", Color(255, 69, 0));
	list.Add("mood", Color(255, 255, 0));
	list.Add("future tense verbs", Color(197, 179, 88));
	list.Add("past tense verbs", Color(255, 192, 203));
	list.Add("article", Color(65, 105, 225));
	list.Add("hope", Color(135, 206, 235));
	list.Add("grief", Color(128, 128, 128));
	list.Add("passion", Color(255, 0, 255));
	list.Add("happiness", Color(128, 0, 128));
	list.Add("anger", Color(255, 165, 0));
	list.Add("love", Color(255, 0, 0));
	list.Add("loss", Color(0, 0, 0));
	list.Add("sorrow", Color(255, 105, 180));
	list.Add("heartache", Color(255, 192, 203));
	list.Add("romance", Color(238, 232, 170));
	list.Add("longing", Color(47, 79, 79));
	list.Add("joy", Color(255, 255, 0));
	list.Add("sadness", Color(70, 130, 180));
	list.Add("relationship", Color(218, 165, 32));
	list.Add("intercourse", Color(204, 0, 0));
	list.Add("family", Color(255, 255, 0));
	list.Add("forgiveness", Color(0, 255, 0));
	list.Add("distance", Color(128, 128, 128));
	list.Add("communication", Color(60, 179, 113));
	list.Add("boundaries", Color(70, 130, 180));
	list.Add("resolution", Color(255, 0, 0));
	list.Add("denial", Color(255, 255, 255));
	list.Add("reconciliation", Color(0, 0, 255));
	list.Add("thoughts", Color(128, 0, 0));
	list.Add("mental state", Color(255, 255, 0));
	list.Add("messages", Color(60, 179, 113));
	list.Add("personal growth", Color(0, 128, 0));
	list.Add("inline rhymes", Color(0, 100, 0));
	list.Add("sarcasm", Color(255, 127, 80));
	list.Add("positivity", Color(152, 251, 152));
	list.Add("superlative adjectives", Color(102, 205, 170));
	list.Add("simile", Color(250, 128, 114));
	list.Add("negativity", Color(255, 192, 203));
	list.Add("emotional progression", Color(255, 140, 0));
	list.Add("tones", Color(255, 69, 0));
	list.Add("moods", Color(233, 194, 138));
	list.Add("possessive pronoun", Color(161, 121, 138));
	list.Add("superlative adjective", Color(233, 101, 138));
	list.Add("modal verb", Color(141, 233, 138));
	list.Add("metaphorical similes", Color(138, 168, 233));
	list.Add("repeated words/lines", Color(169, 233, 138));
	list.Add("phrases", Color(232, 138, 233));
	list.Add("adjectival phrase", Color(233, 212, 138));
	list.Add("repeated phrases", Color(138, 201, 233));
	list.Add("nouns", Color(186, 138, 233));
	list.Add("onsimilars", Color(138, 185, 233));
	list.Add("rhyming words", Color(237, 138, 233));
	list.Add("concerns", Color(233, 138, 206));
	list.Add("imperative verb", Color(138, 233, 173));
	list.Add("dramatic ending", Color(138, 233, 236));
	list.Add("passive and active voice", Color(202, 138, 233));
	list.Add("auxiliary adjective", Color(233, 138, 198));
	list.Add("personal pronoun", Color(138, 236, 233));
	list.Add("possessive determiner", Color(138, 233, 212));
	list.Add("question word", Color(242, 233, 138));
	list.Add("books", Color(170, 138, 233));
	list.Add("intimacy", Color(138, 233, 185));
	list.Add("adjectives", Color(216, 138, 233));
	list.Add("theme", Color(233, 138, 221));
	list.Add("repetitive phrase", Color(138, 245, 233));
	list.Add("statements of affirmation and negation", Color(233, 234, 138));
	list.Add("tenses", Color(174, 233, 138));
	list.Add("structural devices", Color(167, 138, 233));
	list.Add("metaphor", Color(150, 138, 233));
	list.Add("communication device", Color(178, 138, 233));
	list.Add("possessive adjective", Color(156, 238, 138));
	list.Add("compound word", Color(233, 138, 158));
	list.Add("contradiction", Color(138, 225, 233));
	list.Add("plural nouns", Color(233, 138, 245));
	list.Add("singular nouns", Color(145, 233, 138));
	list.Add("possesive adjectives", Color(233, 178, 138));
	list.Add("modifiers", Color(190, 138, 233));
	list.Add("dynamic words/describe movement", Color(138, 240, 233));
	list.Add("parallelism", Color(138, 233, 192));
	list.Add("infatuation", Color(201, 138, 233));
	list.Add("repetition of hook", Color(233, 138, 245));
	list.Add("tonal", Color(138, 233, 185));
	list.Add("movement words", Color(172, 233, 138));
	list.Add("present tense verbs", Color(233, 245, 138));
	list.Add("personifications", Color(184, 138, 233));
	list.Add("exclamation", Color(138, 233, 211));
	list.Add("intonation", Color(178, 233, 138));
	list.Add("posessive pronoun", Color(233, 156, 138));
	list.Add("approximate rhyme", Color(221, 138, 233));
	list.Add("comparative adjectives", Color(138, 233, 204));
	list.Add("prepositions", Color(233, 208, 138));
	list.Add("parts of speech", Color(233, 245, 138));
	list.Add("possession", Color(222, 138, 233));
	list.Add("posessive pronouns", Color(139, 233, 138));
	list.Add("nouns as adjectives", Color(190, 233, 138));
	list.Add("curses and swear words", Color(238, 138, 233));
	list.Add("possession pronoun", Color(225, 138, 233));
	list.Add("words related to emotion/themes", Color(233, 172, 138));
	list.Add("numerical adjective", Color(138, 233, 239));
	list.Add("emotivity", Color(190, 138, 233));
	list.Add("proper nouns", Color(153, 138, 233));
	list.Add("response to concern", Color(233, 185, 138));
	list.Add("consequences of insanity", Color(245, 233, 138));
	list.Add("figurative language", Color(138, 233, 145));
	list.Add("sex", Color(147, 233, 138));
	list.Add("writing devices", Color(233, 222, 138));
	list.Add("grief/loss", Color(138, 240, 233));
	list.Add("sorrow/heartache", Color(233, 178, 138));
	list.Add("verb phrase", Color(156, 233, 138));
	list.Add("pronoun agreement", Color(138, 233, 170));
	list.Add("simple present tense verbs", Color(233, 238, 138));
	list.Add("simple past tense verbs", Color(138, 233, 189));
	list.Add("rhyming words/phrases", Color(247, 138, 233));
	list.Add("depicting movement", Color(138, 245, 233));
	list.Add("repetitive chorus", Color(235, 138, 233));
	list.Add("possession pronouns", Color(164, 138, 233));
	list.Add("relationships", Color(156, 233, 138));
	list.Add("words that depict movements", Color(138, 233, 163));
	list.Add("strong emotions", Color(232, 138, 233));
	list.Add("similes", Color(138, 233, 204));
	list.Add("comparative and superlative adjectives", Color(194, 138, 233));
	list.Add("extra word groups specific to the song", Color(138, 186, 233));
	list.Add("periphrasis", Color(233, 154, 138));
	list.Add("frequency", Color(125, 233, 138));
	list.Add("modals", Color(233, 125, 138));
	list.Add("adverbial phrases", Color(138, 233, 231));
	list.Add("words that represent themes", Color(147, 138, 233));
	list.Add("rhyme scheme", Color(233, 152, 138));
	list.Add("rhetorical question", Color(230, 233, 138));
	list.Add("determiners", Color(138, 233, 230));
	list.Add("superlative", Color(234, 233, 138));
	list.Add("indefinite pronouns", Color(228, 138, 233));
	list.Add("possessive adjectives", Color(233, 196, 138));
	list.Add("possession determiner", Color(138, 233, 175));
	list.Add("contraction", Color(233, 138, 244));
	list.Add("sibilance", Color(243, 138, 233));
	list.Add("compound verbs", Color(138, 233, 187));
	list.Add("repeated word", Color(205, 183, 138));
	list.Add("emotional word", Color(138, 233, 190));
	list.Add("strong verb", Color(233, 138, 233));
	list.Add("weak verb", Color(138, 233, 126));
	list.Add("onomatopoeic word", Color(136, 138, 233));
	list.Add("word that depicts movement", Color(218, 233, 138));
	list.Add("symbolic word", Color(138, 223, 233));
	list.Add("descriptive word", Color(233, 129, 138));
	list.Add("word with multiple meanings", Color(138, 233, 214));
	list.Add("personalization", Color(136, 233, 138));
	list.Add("comparative/superlative adjectives", Color(138, 236, 233));
	list.Add("emotional words and phrases", Color(232, 183, 138));
	list.Add("song structure", Color(138, 233, 155));
	list.Add("emotions", Color(172, 138, 233));
	list.Add("emotion", Color(138, 233, 131));
	list.Add("possible themes", Color(233, 168, 138));
	list.Add("symbolism", Color(138, 233, 203));
	list.Add("active voice verbs", Color(220, 138, 233));
	list.Add("passive voice verbs", Color(138, 233, 178));
	list.Add("contradictory words", Color(233, 223, 138));
	list.Add("numeric", Color(138, 220, 233));
	list.Add("emotions/themes", Color(233, 124, 138));
	list.Add("noun phrase", Color(230, 233, 138));
	list.Add("adjective phrase", Color(136, 138, 233));
	list.Add("possessive pronouns", Color(189, 233, 138));
	list.Add("address", Color(138, 233, 196));
	list.Add("image severity", Color(233, 228, 138));
	list.Add("relative pronouns", Color(243, 138, 233));
	list.Add("topics/themes", Color(146, 233, 138));
	list.Add("positive/negative", Color(138, 233, 128));
	list.Add("emotional states/themes", Color(138, 230, 233));
	list.Add("pair's romantic components", Color(233, 134, 138));
	list.Add("resolutions", Color(222, 233, 138));
	list.Add("extended metaphors", Color(138, 233, 126));
	list.Add("exclamations", Color(174, 138, 233));
	list.Add("adjective pronouns", Color(138, 233, 169));
	list.Add("repetitive words/phrases", Color(233, 225, 138));
	list.Add("positivity/negativity", Color(138, 233, 236));
	list.Add("emotions and feelings", Color(245, 233, 138));
	list.Add("loneliness", Color(138, 233, 128));
	list.Add("proper noun", Color(183, 233, 138));
	list.Add("connected speech", Color(138, 233, 163));
	list.Add("distances", Color(233, 140, 138));
	list.Add("55-anger", Color(255, 77, 77));
	list.Add("possession adjectives", Color(173, 154, 103));
	list.Add("themed words", Color(146, 212, 240));
	list.Add("prepositional phrase", Color(255, 242, 153));
	list.Add("hyperboles", Color(249, 191, 220));
	list.Add("disillusion", Color(216, 191, 216));
	list.Add("active-voice", Color(0, 153, 0));
	list.Add("onomatopoetic words", Color(255, 153, 0));
	list.Add("noun phrases", Color(255, 218, 185));
	list.Add("icons", Color(255, 204, 0));
	list.Add("act", Color(255, 111, 97));
	list.Add("hook", Color(204, 204, 255));
	list.Add("slang words", Color(162, 255, 178));
	list.Add("rhythmic words", Color(0, 204, 204));
	list.Add("lyrical structure", Color(255, 179, 217));
	list.Add("ideas", Color(102, 204, 255));
	list.Add("adjacent", Color(255, 77, 166));
	list.Add("possessive adjectives", Color(204, 181, 141));
	list.Add("verb tense", Color(153, 204, 255));
	list.Add("verse length", Color(0, 153, 153));
	list.Add("line length", Color(255, 153, 153));
	list.Add("symbols", Color(255, 153, 0));
	list.Add("comparative adjective", Color(255, 102, 255));
	list.Add("question words", Color(204, 153, 255));
	list.Add("sevens", Color(204, 255, 255));
	list.Add("assonance", Color(153, 153, 0));
	list.Add("indirect speech/reported speech", Color(255, 102, 102));
	list.Add("ony", Color(255, 204, 153));
	list.Add("indirect speech", Color(204, 204, 153));
	list.Add("personification", Color(255, 181, 197));
	list.Add("superlatives adjectives", Color(179, 238, 58));
	list.Add("definite article", Color(153, 252, 255));
	list.Add("determiner", Color(255, 255, 102));
	list.Add("slang", Color(171, 222, 255));
	list.Add("adverb/conjunction", Color(255, 204, 204));
	list.Add("letter", Color(255, 204, 204));
	list.Add("possessive marker", Color(177, 156, 217));
	list.Add("preposition/adverb", Color(255, 255, 153));
	list.Add("number", Color(255, 255, 153));
	list.Add("verb/noun", Color(255, 153, 255));
	list.Add("verb/adjective", Color(219, 144, 71));
	list.Add("adjective/verb", Color(219, 144, 71));
	list.Add("title", Color(153, 255, 255));
	list.Add("abbreviation", Color(204, 255, 255));
	list.Add("noun/adjective", Color(153, 204, 0));
	list.Add("numeral", Color(255, 102, 102));
	list.Add("adverb/conjunction", Color(155, 123, 255));
	list.Add("acronym", Color(204, 255, 204));
	return list;
}




#define COLOR_GROUP_COUNT (3+6*3)
int GetColorGroupCount() {
	return COLOR_GROUP_COUNT;
}

const Color& GetGroupColor(int i) {
	static Color clrs[COLOR_GROUP_COUNT] = {
		Color(255, 255, 255),
		Color(128, 128, 128),
		
		Color(255, 0, 0),
		Color(255, 0, 255),
		Color(0, 0, 255),
		Color(0, 255, 255),
		Color(0, 255, 0),
		Color(255, 255, 0),
		
		Color(255, 128, 128),
		Color(255, 128, 255),
		Color(128, 128, 255),
		Color(128, 255, 255),
		Color(128, 255, 128),
		Color(255, 255, 128),
		
		Color(128, 0, 0),
		Color(128, 0, 128),
		Color(0, 0, 128),
		Color(0, 128, 128),
		Color(0, 128, 0),
		Color(128, 128, 0),
		
		Color(0, 0, 0)
	};
	i = max(min(COLOR_GROUP_COUNT-1, i), 0);
	return clrs[i];
}

int GetColorGroup(const Color& clr) {
	const Color* begin = &GetGroupColor(0);
	const Color* it = begin;
	int count = GetColorGroupCount();
	const Color* end = begin + count;
	
	int closest_dist = GetColorDistance(*it, clr);
	int closest_group = 0;
	it++;
	while (it != end) {
		int dist = GetColorDistance(*it, clr);
		if (dist < closest_dist) {
			closest_group = (int)(it - begin);
			closest_dist = dist;
		}
		it++;
	}
	
	return closest_group;
}



void SetColoredListValue(ArrayCtrl& list, int row, int col, const String& txt, Color clr, bool blend) {
	if (blend) {
		list.Set(row, col, AttrText(txt)
			.NormalPaper(Blend(clr, White(), 128+64)).NormalInk(Black())
			.Paper(Blend(clr, GrayColor())).Ink(White())
		);
	}
	else {
		list.Set(row, col, AttrText(txt)
			.NormalPaper(clr).NormalInk(Black())
			.Paper(Blend(clr, GrayColor(64))).Ink(White())
		);
	}
}










Color HSVToRGB(double H, double S, double V) {
	double r = 0, g = 0, b = 0;
	
	H *= 360.;
	
	if (S == 0)
	{
		r = V;
		g = V;
		b = V;
	}
	else
	{
		int i;
		double f, p, q, t;

		if (H == 360)
			H = 0;
		else
			H = H / 60;

		i = (int)trunc(H);
		f = H - i;

		p = V * (1.0 - S);
		q = V * (1.0 - (S * f));
		t = V * (1.0 - (S * (1.0 - f)));

		switch (i)
		{
		case 0:
			r = V;
			g = t;
			b = p;
			break;

		case 1:
			r = q;
			g = V;
			b = p;
			break;

		case 2:
			r = p;
			g = V;
			b = t;
			break;

		case 3:
			r = p;
			g = q;
			b = V;
			break;

		case 4:
			r = t;
			g = p;
			b = V;
			break;

		default:
			r = V;
			g = p;
			b = q;
			break;
		}

	}
	
	if (0) {
		DUMP(r);
		DUMP(g);
		DUMP(b);
	}
	RGBA rgb;
	rgb.r = (byte)(r * 255);
	rgb.g = (byte)(g * 255);
	rgb.b = (byte)(b * 255);
	rgb.a = 255;
	
	return rgb;
}


END_TEXTLIB_NAMESPACE

