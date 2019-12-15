/*AoC day 3 part 1
Author(s)		: Lukas Mirow
Date of creation	: 12/09/2019
*/

#include "shared_classes.cpp"
#include <iostream>
using namespace std;

UNSIGNED_VAL_TYPE calc_distance_from_center(Point pt)
{
	return abs(pt.horizontal) + abs(pt.vertical);
}

bool is_point_in_vector(const Point pt, const vector<Point>& v)
{
	for (const Point vpt : v)
		if (pt.horizontal == vpt.horizontal and pt.vertical == vpt.vertical)
			return true;
	return false;
}

bool is_point_center(const Point pt)
{
	return pt.horizontal == 0 and pt.vertical == 0;
}

UNSIGNED_VAL_TYPE count_delay_in_wire(const Point& pt, const vector<Point>& wire)
{
	UNSIGNED_VAL_TYPE res = 0;
	for (const Point wire_pt : wire)
	{
		res++;
		if (not is_point_center(wire_pt) and wire_pt.horizontal == pt.horizontal and wire_pt.vertical == pt.vertical)
			return res;
	}
	return -1;
}

int main(int argc, char **argv)
{
	Wire red, blue;
	UNSIGNED_VAL_TYPE current_closest_distance = -1;
	UNSIGNED_VAL_TYPE this_delay, first_wire_delay = 0, current_shortest_delay = -1;
	vector<Point> red_points, blue_points;
	// Test data:
	// red.right(98).up(47).right(26).down(63).right(33).up(87).left(62).down(20).right(33).up(53).right(51);
	// blue.up(98).right(91).down(20).right(16).down(67).right(40).up(7).right(15).up(6).right(7);
	red.right(1001).down(890).right(317).up(322).left(481).down(597).left(997).up(390).left(78).down(287).left(401).up(638).right(493).down(493).right(237).up(29).right(333).down(466).left(189).down(634).right(976).up(934).right(597).up(62).left(800).up(229).right(625).down(927).left(629).down(334).left(727).up(4).right(716).up(20).left(284).up(655).right(486).up(883).right(194).up(49).left(845).down(960).right(304).down(811).left(38).up(114).right(477).down(318).left(308).up(445).left(26).down(44).right(750).down(12).right(85).down(146).right(353).up(715).right(294).down(595).left(954).up(267).left(927).up(383).left(392).down(866).left(195).up(487).left(959).up(630).right(528).down(482).right(932).down(541).left(658).down(171).left(964).up(687).right(118).up(53).left(81).down(381).right(592).up(238).left(391).up(399).right(444).up(921).right(706).up(925).right(204).down(220).left(595).up(489).right(621).down(15).right(104).down(567).left(664).down(54).right(683).up(654).right(441).down(748).left(212).down(147).left(699).up(296).left(842).up(230).left(684).down(470).right(247).down(421).right(38).down(757).left(985).up(791).right(112).up(494).right(929).down(726).left(522).up(381).right(184).down(492).left(517).down(819).right(487).down(620).right(292).down(206).right(254).down(175).left(16).up(924).right(838).down(423).right(756).down(720).left(555).up(449).left(952).down(610).left(427).up(391).right(520).down(957).right(349).down(670).left(678).up(467).right(804).up(757).left(342).up(808).right(261).down(597).left(949).up(162).right(3).down(712).left(799).up(531).right(879).down(355).right(325).down(173).left(303).up(679).left(432).down(421).right(613).up(431).left(207).down(669).right(828).down(685).right(808).up(494).right(821).up(195).left(538).up(16).left(835).down(442).left(77).up(309).left(490).up(918).left(6).down(200).left(412).down(272).left(416).up(774).left(75).down(23).left(193).down(574).right(807).down(382).left(314).down(885).right(212).down(806).left(183).up(345).left(932).up(58).left(37).up(471).right(345).up(678).right(283).up(644).left(559).up(892).left(26).down(358).left(652).down(606).left(251).up(791).left(980).down(718).left(14).down(367).right(997).down(812).right(504).down(474).left(531).up(708).right(660).up(253).left(86).down(491).right(971).up(608).left(166).up(659).right(167).up(92).left(600).up(20).right(28).up(852).right(972).down(409).left(719).down(634).right(787).down(796).left(546).down(857).left(987).up(111).left(916).down(108).right(537).up(931).right(308).up(385).left(258).down(171).right(797).up(641).right(798).down(723).right(600).down(710).right(436).up(587).right(16).down(564).left(14).down(651).right(709).down(587).right(626).up(270).right(802).up(937).right(31).up(518).left(187).down(738).right(562).down(238).right(272).down(403).right(788).down(859).left(704).down(621).left(547).down(737).left(958).up(311).left(927);
	blue.left(1007).up(199).left(531).down(379).left(313).up(768).left(87).up(879).right(659).up(307).left(551).down(964).left(725).down(393).right(239).down(454).right(664).up(402).right(100).down(62).right(53).down(503).right(918).up(998).left(843).down(142).right(561).up(461).right(723).down(915).left(217).down(126).left(673).up(171).right(131).up(518).right(298).up(99).left(852).down(799).left(159).up(161).right(569).down(802).left(391).down(553).left(839).up(954).right(502).up(351).right(851).down(11).left(243).down(774).left(642).up(613).right(376).up(867).left(357).down(887).left(184).down(298).right(406).up(912).right(900).down(348).left(779).up(494).right(240).down(712).right(849).down(684).right(475).down(449).left(94).up(630).left(770).down(426).left(304).down(869).right(740).down(377).right(435).down(719).left(815).down(211).right(391).up(484).right(350).up(599).right(57).up(210).right(95).up(500).left(947).down(649).right(615).down(404).left(953).down(468).right(380).up(215).right(82).down(872).right(150).down(347).left(700).down(450).left(90).up(803).left(593).up(296).right(408).up(667).right(407).up(725).right(197).up(269).right(115).down(758).right(558).up(62).left(519).up(308).right(259).up(869).left(846).up(3).right(592).down(357).right(633).down(909).left(826).up(165).left(190).down(821).left(525).up(404).right(63).down(214).right(265).up(74).left(715).up(461).left(840).down(647).right(782).down(655).right(72).down(601).left(435).up(549).left(108).up(687).right(836).down(975).left(972).up(813).right(258).up(703).right(90).down(438).right(434).down(818).right(184).down(886).right(271).up(31).left(506).up(395).left(274).up(455).right(699).up(889).left(162).up(771).right(752).up(317).right(267).down(959).right(473).up(58).right(552).up(51).right(637).down(726).right(713).down(530).left(209).down(824).right(275).down(207).right(357).down(373).left(169).up(880).left(636).up(409).right(67).down(740).right(225).down(272).right(114).up(970).right(51).up(230).right(859).up(820).left(979).down(153).right(16).down(883).left(542).up(806).left(523).down(752).left(712).up(55).left(739).up(746).right(910).down(873).right(108).down(558).left(54).down(619).left(444).up(941).right(613).up(478).left(839).down(910).right(426).down(614).left(622).up(928).left(65).down(644).left(208).up(971).left(939).up(874).right(827).up(672).left(620).up(140).left(493).down(637).left(767).up(831).right(874).up(468).right(648).up(714).right(294).down(606).left(375).down(962).left(105).down(919).left(486).down(771).left(827).down(196).left(408).up(217).left(960).down(633).left(850).up(805).left(188).up(566).left(884).down(212).left(677).down(204).right(257).down(409).right(309).down(783).left(773).down(588).left(302).up(129).left(550).up(919).left(482).up(563).right(290).up(690).right(586).down(460).left(771).down(63).right(451).down(591).left(861).down(598).left(432).up(818).left(182);
	red_points = red.get_points();
	blue_points = blue.get_points();
	for (const Point pt : red_points)
	{
		first_wire_delay++;
		cerr << "Checking point " << pt.horizontal << 'x' << pt.vertical << endl;
		if (not is_point_center(pt) and is_point_in_vector(pt, blue_points))
		{
			cerr << "Yep!" << endl;
			UNSIGNED_VAL_TYPE this_distance = calc_distance_from_center(pt);
			if (calc_distance_from_center(pt) < current_closest_distance)
				current_closest_distance = this_distance;
			this_delay = first_wire_delay + count_delay_in_wire(pt, blue_points);
			if (this_delay < current_shortest_delay)
				current_shortest_delay = this_delay;
		}
		else
			cerr << "Nope..." << endl;
	}
	cout << "Closest distance to center: " << current_closest_distance << endl;
	cout << "Shortest delay: " << current_shortest_delay << endl;
	return 0;
}
