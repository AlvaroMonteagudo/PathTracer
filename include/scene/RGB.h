/**
 *  @file    RGB.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    15/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for RGB class
 *  Color definition with three values: red, green and blue.
 *  It could be enlarge to handle HSV, HSL or other diferent kind of
 *  color representations.
 */

#pragma once

#include <ostream>
#include <fstream>

using namespace std;

class RGB{

public:

    /**
     * Color constructor
     * @param red value
     * @param green value
     * @param blue value
     */
    RGB(float red = 0, float green = 0, float blue = 0);

    /// GETTERS
    float getRed() const;

    float getBlue() const;

    float getGreen() const;

    float getMean() const;

    float getMax() const;

    float getMin() const;

    /// SETTERS

    void setRed(float red);

    void setBlue(float blue);

    void setGreen(float green);

    /// Useful operators
    RGB operator + (const RGB &color) const;

    void operator += (const RGB &color);

    RGB operator * (const RGB &color) const;

    void operator *= (const RGB &color) ;

    RGB operator * (float value) const;

    void operator *= (float value);

    RGB operator / (float value) const;

    void operator /= (float value);

    bool operator ==(const RGB &rhs) const;

    bool operator !=(const RGB &rhs) const;

    friend std::ostream& operator << (std::ostream &os, const RGB &rgb);

    /**
     * Operator to write color to a file
     * @param file to write color
     * @param rgb data to be written
     * @return file with rgb data values written
     */
    friend std::ofstream& operator << (std::ofstream &file, const RGB &rgb);

    RGB toInt();

    RGB cvtToSepia();

    RGB cvtToBW();

private:

    float red, blue, green;

};

/// RGB common used values
#define     MAROON		            RGB(128,0,0) / 255.0f
#define 	DARK_RED		        RGB(139,0,0) / 255.0f
#define 	BROWN		            RGB(165,42,42) / 255.0f
#define 	FIREBRICK		        RGB(178,34,34) / 255.0f
#define 	CRIMSON		            RGB(220,20,60) / 255.0f
#define     RED                     RGB(242,0,0) / 255.0f
#define 	TOMATO		            RGB(242,99,71) / 255.0f
#define 	CORAL		            RGB(242,127,80) / 255.0f
#define 	INDIAN_RED		        RGB(205,92,92) / 255.0f
#define 	LIGHT_CORAL		        RGB(240,128,128) / 255.0f
#define 	DARK_SALMON		        RGB(233,150,122) / 255.0f
#define 	SALMON		            RGB(237,128,114) / 255.0f
#define 	LIGHT_SALMON		    RGB(242,160,122) / 255.0f
#define 	ORANGE_RED		        RGB(242,69,0) / 255.0f
#define 	DARK_ORANGE		        RGB(242,140,0) / 255.0f
#define 	ORANGE		            RGB(242,165,0) / 255.0f
#define 	GOLD		            RGB(242,215,0) / 255.0f
#define 	DARK_GOLDEN_ROD		    RGB(184,134,11) / 255.0f
#define 	GOLDER_ROD		        RGB(218,165,32) / 255.0f
#define 	PALE_GOLDEN_ROD		    RGB(238,232,170) / 255.0f
#define 	DARK_KHAKI		        RGB(189,183,107) / 255.0f
#define 	KHAKI		            RGB(240,230,140) / 255.0f
#define 	OLIVE		            RGB(128,128,0) / 255.0f
#define 	YELLOW		            RGB(242,242,0) / 255.0f
#define 	YELLOW_GREEN		    RGB(154,205,50) / 255.0f
#define 	DARK_OLIVE_GREEN		RGB(85,107,47) / 255.0f
#define 	OLIVE_DRAB		        RGB(107,142,35) / 255.0f
#define 	LAWN_GREEN		        RGB(124,239,0) / 255.0f
#define 	CHART_REUSE		        RGB(127,242,0) / 255.0f
#define 	GREEN_YELLOW		    RGB(173,242,47) / 255.0f
#define 	DARK_GREEN		        RGB(0,100,0) / 255.0f
#define 	GREEN		            RGB(0,128,0) / 255.0f
#define 	FOREST_GREEN		    RGB(34,139,34) / 255.0f
#define     LIME                    RGB(0, 242, 0) / 255.0f
#define 	LIME_GREEN		        RGB(50,205,50) / 255.0f
#define 	LIGHT_GREEN		        RGB(144,238,144) / 255.0f
#define 	PALE_GREEN		        RGB(152,238,152) / 255.0f
#define 	DARK_SEA_GREEN		    RGB(143,188,143) / 255.0f
#define 	MEDIUM_SPRING_GREEN		RGB(0,237,154) / 255.0f
#define 	SPRING_GREEN		    RGB(0,242,127) / 255.0f
#define 	SEA_GREEN		        RGB(46,139,87) / 255.0f
#define 	MEDIUM_AQUA_MARINE		RGB(102,205,170) / 255.0f
#define 	MEDIUM_SEA_GREEN		RGB(60,179,113) / 255.0f
#define 	LIGHT_SEA_GREEN		    RGB(32,178,170) / 255.0f
#define 	DARK_SLATE_GRAY		    RGB(47,79,79) / 255.0f
#define 	TEAL		            RGB(0,128,128) / 255.0f
#define 	DARK_CYAN		        RGB(0,139,139) / 255.0f
#define 	AQUA		            RGB(0,242,242) / 255.0f
#define 	CYAN		            RGB(0,242,242) / 255.0f
#define 	LIGHT_CYAN		        RGB(224,242,242) / 255.0f
#define 	DARK_TURQUOISE		    RGB(0,206,209) / 255.0f
#define 	TURQUOISE		        RGB(64,224,208) / 255.0f
#define 	MEDIUM_TURQUOISE		RGB(72,209,204) / 255.0f
#define 	PALE_TURQUOISE		    RGB(175,238,238) / 255.0f
#define 	AQUA_MARINE		        RGB(127,242,212) / 255.0f
#define 	POWDER_BLUE		        RGB(176,224,230) / 255.0f
#define 	CADET_BLUE		        RGB(95,158,160) / 255.0f
#define 	STEEL_BLUE		        RGB(70,130,180) / 255.0f
#define 	CORN_FLOWER_BLUE		RGB(100,149,237) / 255.0f
#define 	DEEP_SKY_BLUE		    RGB(0,191,242) / 255.0f
#define 	DODGER_BLUE		        RGB(30,144,242) / 255.0f
#define 	LIGHT_BLUE		        RGB(173,216,230) / 255.0f
#define 	SKY_BLUE		        RGB(135,206,235) / 255.0f
#define 	LIGHT_SKY_BLUE		    RGB(135,206,237) / 255.0f
#define 	MIDNIGHT_BLUE		    RGB(25,25,112) / 255.0f
#define 	NAVY		            RGB(0,0,128) / 255.0f
#define 	DARK_BLUE		        RGB(0,0,139) / 255.0f
#define 	MEDIUM_BLUE		        RGB(0,0,205) / 255.0f
#define 	BLUE		            RGB(0,0,242) / 255.0f
#define 	ROYAL_BLUE		        RGB(65,105,225) / 255.0f
#define 	BLUE_VIOLET		        RGB(138,43,226) / 255.0f
#define 	INDIGO		            RGB(75,0,130) / 255.0f
#define 	DARK_SLATE_BLUE		    RGB(72,61,139) / 255.0f
#define 	SLATE_BLUE		        RGB(106,90,205) / 255.0f
#define 	MEDIUM_SLATE_BLUE		RGB(123,104,238) / 255.0f
#define 	MEDIUM_PURPLE		    RGB(147,112,219) / 255.0f
#define 	DARK_MAGENTE		    RGB(139,0,139) / 255.0f
#define 	DARK_VIOLET		        RGB(148,0,211) / 255.0f
#define 	DARK_ORCHID		        RGB(153,50,204) / 255.0f
#define 	MEDIUM_ORCHID		    RGB(186,85,211) / 255.0f
#define 	PURPLE		            RGB(128,0,128) / 255.0f
#define 	THISTLE		            RGB(216,191,216) / 255.0f
#define 	PLUM		            RGB(221,160,221) / 255.0f
#define 	VIOLET		            RGB(238,130,238) / 255.0f
#define 	MAGENTA		            RGB(242,0,242) / 255.0f
#define 	ORCHID		            RGB(218,112,214) / 255.0f
#define 	MEDIUM_VIOLET_RED 	    RGB(199,21,133) / 255.0f
#define 	PALE_VIOLET_RED		    RGB(219,112,147) / 255.0f
#define 	DEEP_PINK		        RGB(242,20,147) / 255.0f
#define 	HOT_PINK		        RGB(242,105,180) / 255.0f
#define 	LIGHT_PINK		        RGB(242,182,193) / 255.0f
#define 	PINK		            RGB(242,192,203) / 255.0f
#define 	ANTIQUE_WHITE   		RGB(237,235,215) / 255.0f
#define 	BEIGE		            RGB(242,242,220) / 255.0f
#define 	BISQUE		            RGB(242,228,196) / 255.0f
#define 	BLANCHED_ALMOND		    RGB(242,235,205) / 255.0f
#define 	WHEAT		            RGB(242,222,179) / 255.0f
#define 	CORN_SILK		        RGB(242,242,220) / 255.0f
#define 	LEMON_CHIFFON		    RGB(242,237,205) / 255.0f
#define 	LIGHT_GOLDEN_YELLOW		RGB(237,237,210) / 255.0f
#define 	LIGHT_YELLOW		    RGB(242,242,224) / 255.0f
#define 	SANDLE_BROWN		    RGB(139,69,19) / 255.0f
#define 	SIENNA		            RGB(160,82,45) / 255.0f
#define 	CHOCOLATE		        RGB(210,105,30) / 255.0f
#define 	PERU		            RGB(205,133,63) / 255.0f
#define 	SANDY_BROWN		        RGB(242,164,96) / 255.0f
#define 	BURLY_WOOD		        RGB(222,184,135) / 255.0f
#define 	TAN		                RGB(210,180,140) / 255.0f
#define 	ROSY_BROWN		        RGB(188,143,143) / 255.0f
#define 	MOCCASIN		        RGB(242,228,181) / 255.0f
#define 	NAVAJO_WHITE		    RGB(242,222,173) / 255.0f
#define 	PEACH_PUFF		        RGB(242,218,185) / 255.0f
#define 	MISTY_ROSE		        RGB(242,228,225) / 255.0f
#define 	LAVENDER_BLUSH		    RGB(242,240,242) / 255.0f
#define 	LINEN		            RGB(237,240,230) / 255.0f
#define 	OLD_LACE		        RGB(240,242,230) / 255.0f
#define 	PAPAYA_WHIP		        RGB(242,239,213) / 255.0f
#define 	SEA_SHELL		        RGB(242,242,238) / 255.0f
#define 	MINC_CREAM		        RGB(242,242,237) / 255.0f
#define 	SLATE_GRAY		        RGB(112,128,144) / 255.0f
#define 	LIGHT_SLATE_GRAY		RGB(119,136,153) / 255.0f
#define 	LIGHT_STEEL_BLUE		RGB(176,196,222) / 255.0f
#define 	LAVENDER		        RGB(230,230,237) / 255.0f
#define 	FLORAL_WHITE		    RGB(242,237,240) / 255.0f
#define 	ALICE_BLUE		        RGB(240,242,242) / 255.0f
#define 	GHOST_WHITE		        RGB(242,242,242) / 255.0f
#define 	HONEYDEW		        RGB(240,242,240) / 255.0f
#define 	IVORY		            RGB(242,242,240) / 255.0f
#define 	AZURE		            RGB(240,242,242) / 255.0f
#define 	SNOW		            RGB(242,237,237) / 255.0f
#define 	BLACK		            RGB(0,0,0)
#define 	DIM_GRAY	            RGB(105,105,105) / 255.0f
#define 	GRAY		            RGB(128,128,128) / 255.0f
#define 	DARK_GRAY		        RGB(169,169,169) / 255.0f
#define 	SILVER		            RGB(192,192,192) / 255.0f
#define 	LIGHT_GRAY		        RGB(211,211,211) / 255.0f
#define 	GAINSBORG		        RGB(220,220,220) / 255.0f
#define 	WHITE		            RGB(242,242,242) / 255.0f
