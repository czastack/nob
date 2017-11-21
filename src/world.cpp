#include <nob/world.hpp>
#include <nob/object.hpp>

#include <nob/shv/main.hpp>

namespace nob {
	namespace world {
		/*
			Reference from
				http://gtaforums.com/topic/858699-completely-clean-world/
				https://github.com/codecat/quinMP/blob/master/StrawberryPie/Scripts/CleanWorld.cpp
		*/
		void no_mans_island(bool toggle) {
			static task tsk;
			if (toggle) {
				if (!tsk) {
					tsk = task([]() {
						ntv::VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::VEHICLE::_0xD4B8E3D1917BC86B(false);
						ntv::VEHICLE::_SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);

						ntv::PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);

						ntv::DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();
						ntv::DECISIONEVENT::SUPPRESS_AGITATION_EVENTS_NEXT_FRAME();

						ntv::VEHICLE::DELETE_ALL_TRAINS();
						ntv::PLAYER::SET_MAX_WANTED_LEVEL(0);

						ntv::VEHICLE::SET_GARBAGE_TRUCKS(false);
						ntv::VEHICLE::SET_RANDOM_BOATS(false);
						ntv::VEHICLE::SET_RANDOM_TRAINS(false);

						ntv::VEHICLE::SET_NUMBER_OF_PARKED_VEHICLES(-1);
						ntv::VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(false);
						ntv::VEHICLE::SET_FAR_DRAW_VEHICLES(false);
						ntv::VEHICLE::_DISPLAY_DISTANT_VEHICLES(false);

						ntv::AUDIO::_FORCE_AMBIENT_SIREN(false);
						ntv::AUDIO::STOP_ALL_ALARMS(true);
					});

					auto pos = player::body().pos();
					ntv::GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(pos.x, pos.y, pos.z, 1000, false, false, false, false);
					ntv::AUDIO::_DISABLE_POLICE_REPORTS();
					for (size_t i = 1; i < 16; ++i) {
						ntv::GAMEPLAY::ENABLE_DISPATCH_SERVICE(i, false);
					}
					ntv::PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0);
					ntv::PED::SET_CREATE_RANDOM_COPS(false);

					ntv::AUDIO::SET_AUDIO_FLAG("LoadMPData", true);
					ntv::AUDIO::SET_AUDIO_FLAG("DisableBarks", true);
					ntv::AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", true);
					ntv::AUDIO::SET_AUDIO_FLAG("PoliceScannerDisabled", true);
					ntv::AUDIO::SET_AUDIO_FLAG("OnlyAllowScriptTriggerPoliceScanner", true);
				}
			} else {
				tsk.del();
			}
		}

		void disable_sp_features(bool toggle) {
			static task tsk;

			if (toggle) {
				if (!tsk) {
					// Reference from https://github.com/codecat/quinMP/blob/master/StrawberryPie/Scripts/CleanWorld.cpp

					tsk = task([]() {
						if (ntv::GAMEPLAY::IS_STUNT_JUMP_IN_PROGRESS()) {
							ntv::GAMEPLAY::CANCEL_STUNT_JUMP();
						}

						if (ntv::GAMEPLAY::GET_MISSION_FLAG()) {
							ntv::GAMEPLAY::SET_MISSION_FLAG(false);
						}

						if (ntv::GAMEPLAY::GET_RANDOM_EVENT_FLAG()) {
							ntv::GAMEPLAY::SET_RANDOM_EVENT_FLAG(false);
						}

						if (ntv::CUTSCENE::IS_CUTSCENE_ACTIVE()) {
							ntv::CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
						}
					});

					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_NO_MORE_TUTORIALS"), 1, 1);
				}
			} else {
				tsk.del();
			}
		}

		const std::array<door, 487> doors {

			// Reference from am_doors

			door{"prop_com_gar_door_01", {1204.5699462890625, 3110.4, 6.57}},
			door{"v_ilev_rc_door2", {467.3716125488281, -1014.4520263671875, 26.53619956970215}},
			door{"v_ilev_rc_door2", {469.9678955078125, -1014.4520263671875, 26.53619956970215}},
			door{"v_ilev_gtdoor02", {464.3612976074219, -984.6779174804688, 43.834400177}},
			door{"v_ilev_ph_door01", {434.75, -980.6099853515625, 30.84}},
			door{"v_ilev_ph_door002", {434.75, -983.219970703125, 30.84}},
			door{"prop_biolab_g_door", {3589.1, 3671.5, 35.0}},
			door{"prop_biolab_g_door", {3587.6, 3663.3, 35.0}},
			door{"v_ilev_bl_shutter2", {3627.7099609375, 3746.719970703125, 27.69}},
			door{"v_ilev_bl_shutter2", {3620.84, 3751.53, 27.69}},
			door{"v_ilev_abbmaindoor", {962.1, -2183.83, 31.06}},
			door{"v_ilev_abbmaindoor2", {961.7899780273438, -2187.08, 31.06}},
			door{"prop_gate_airport_01", {-1138.469970703125, -2730.449951171875, 12.95}},
			door{"prop_gate_airport_01", {-1151.204345703125, -2723.102294921875, 12.946}},
			door{"prop_gate_airport_01", {-977.5173950195312, -2837.264404296875, 12.954899787902832}},
			door{"prop_gate_airport_01", {-990.2963256835938, -2829.88720703125, 12.949899673461914}},
			door{"prop_facgate_01", {-1213.4, -2079.3, 12.907}},
			door{"prop_fnclink_02gate6_r", {-967.4473266601562, -2778.4951171875, 14.409}},
			door{"prop_fnclink_02gate6_l", {-974.5734252929688, -2774.380859375, 14.409899711608887}},
			door{"prop_fnclink_02gate6_r", {-971.101806640625, -2776.385498046875, 14.409}},
			door{"prop_fnclink_02gate6_l", {-970.9188232421875, -2776.49072265625, 14.409}},
			door{"prop_fnclink_02gate6_r", {-935.21142578125, -2767.396728515625, 14.388199806213379}},
			door{"prop_fnclink_02gate6_l", {-933.1580810546875, -2763.95458984375, 14.388199806213379}},
			door{"prop_fnclink_02gate6_r", {-933.0535278320312, -2763.779296875, 14.388199806213379}},
			door{"prop_fnclink_02gate6_l", {-931.0001831054688, -2760.337158203125, 14.388199806213379}},
			door{"prop_fnclink_02gate6_r", {-773.2437744140625, -2842.677490234375, 14.271499633789062}},
			door{"prop_fnclink_02gate6_l", {-769.7720947265625, -2844.681884765625, 14.271499633789062}},
			door{"prop_fnclink_02gate6_r", {-769.6071166992188, -2844.777099609375, 14.271499633789062}},
			door{"prop_fnclink_02gate6_l", {-766.1353759765625, -2846.781494140625, 14.271499633789062}},
			door{"prop_fnclink_09gate1", {-828.9456176757812, -2964.3037109375, 14.275799751281738}},
			door{"prop_fnclink_09gate1", {907.8, -3100.8740234375, 14.280799865722656}},
			door{"prop_fnclink_09gate1", {-833.4395141601562, -3186.70947265625, 14.267}},
			door{"prop_fnclink_09gate1", {-830.0543823242188, -3391.162841796875, 14.197199821472168}},
			door{"prop_fnclink_09gate1", {-913.0833740234375, -3534.9697265625, 14.1924}},
			door{"prop_fnclink_09gate1", {-971.6149291992188, -3549.152099609375, 14.2727}},
			door{"prop_fnclink_09gate1", {-1017.6920776367188, -3563.21728515625, 14.2767}},
			door{"prop_fnclink_09gate1", {-1146.8314208984375, -3546.63818359375, 14.259499549865723}},
			door{"prop_fnclink_09gate1", {-1260.8966064453125, -3480.763916015625, 14.1721}},
			door{"prop_fnclink_09gate1", {-1351.1328125, -3404.16162109375, 14.1721}},
			door{"prop_fnclink_09gate1", {-1409.50732421875, -3370.46142578125, 14.2068}},
			door{"prop_fnclink_09gate1", {-1831.803955078125, -3224.96630859375, 14.3119}},
			door{"prop_fnclink_09gate1", {-1942.289306640625, -3161.1904296875, 14.2981}},
			door{"prop_fnclink_09gate1", {-1927.5634765625, -3076.26904296875, 14.456899642944336}},
			door{"prop_fnclink_09gate1", {-1951.695556640625, -3003.845703125, 14.4418}},
			door{"prop_fnclink_09gate1", {-1836.875, -2804.968994140625, 14.4557}},
			door{"prop_fnclink_09gate1", {-1802.6915283203125, -2745.761474609375, 14.448}},
			door{"prop_facgate_01", {-1099.53076171875, -2020.8026123046875, 12.1745}},
			door{"prop_facgate_01", {-994.4995727539062, -2341.648193359375, 12.9448}},
			door{"prop_facgate_01", {-984.0709228515625, -2348.4, 12.9448}},
			door{"prop_gate_airport_01", {-1008.0708, -2406.7509765625, 12.977}},
			door{"prop_gate_airport_01", {-1015.4854125976562, -2419.582763671875, 12.9586}},
			door{"v_ilev_lester_doorfront", {1273.8199462890625, 1720.6999999999998, 54.919999999999995}},
			door{"v_ilev_tort_door", {134.39999999999998, -2204.1, 7.52}},
			door{"v_ilev_janitor_frontdoor", {-107.5373, -9.018099784851074, 70.6707992553711}},
			door{"v_ilev_deviantfrontdoor", {-128.33, -1457.17, 37.94}},
			door{"v_ilev_po_door", {-1910.5799560546875, -576.01, 19.25}},
			door{"v_ilev_ra_door3", {1395.92, 1142.9, 114.79}},
			door{"v_ilev_ra_door3", {1395.92, 1140.6999999999998, 114.79}},
			door{"v_ilev_ra_door1_l", {1390.52, 1163.43994140625, 114.38}},
			door{"v_ilev_ra_door1_r", {1390.52, 1161.24, 114.38}},
			door{"v_ilev_ra_door1_l", {1408.0699462890625, 1158.969970703125, 114.48}},
			door{"v_ilev_ra_door1_r", {1408.0699462890625, 1161.17, 114.48}},
			door{"v_ilev_ra_door1_l", {1409.29, 1146.25, 114.49}},
			door{"v_ilev_ra_door1_r", {1409.29, 1148.449951171875, 114.49}},
			door{"v_ilev_bl_door_l", {-1387.05, -586.58, 30.47}},
			door{"v_ilev_bl_door_r", {1389.24, -588.0, 30.47}},
			door{"prop_sec_gate_01c", {25.03, 664.6, 31.04}},
			door{"prop_sec_gate_01d", {-72.75, -682.1699829101562, 33.27}},
			door{"v_ilev_bank4door02", {-111.48, 6463.93994140625, 31.985}},
			door{"v_ilev_bank4door01", {-109.65, 6462.10986328125, 31.985}},
			door{"hei_v_ilev_bk_gate_pris", {256.3116149902344, 220.65789794921875, 106.42960357666016}},
			door{"hei_v_ilev_bk_gate2_pris", {262.1980895996094, 222.518798828125, 106.42960357666016}},
			door{"v_ilev_genbankdoor1", {-2965.821044921875, 481.63, 16.048}},
			door{"v_ilev_genbankdoor2", {-2965.7099609375, 484.218994140625, 16.048}},
			door{"v_ilev_genbankdoor1", {1176.49, 2703.610107421875, 38.44}},
			door{"v_ilev_genbankdoor2", {1173.9, 2703.610107421875, 38.44}},
			door{"v_ilev_genbankdoor1", {1656.25, 4852.240234375, 42.35}},
			door{"v_ilev_genbankdoor2", {1656.5699462890625, 4849.66015625, 42.35}},
			door{"v_ilev_genbankdoor1", {-1215.39, -328.5199890136719, 38.13}},
			door{"v_ilev_genbankdoor2", {-1213.0699462890625, -327.35, 38.13}},
			door{"v_ilev_genbankdoor1", {149.63, -1037.22998046875, 29.72}},
			door{"v_ilev_genbankdoor2", {152.06, 1038.12, 29.72}},
			door{"v_ilev_genbankdoor1", {313.96, -275.6, 54.52}},
			door{"v_ilev_genbankdoor2", {316.39, 276.49, 54.52}},
			door{"v_ilev_genbankdoor2", {-348.8109130859375, -47.2621, 49.3876}},
			door{"v_ilev_genbankdoor1", {-351.2597961425781, -46.4122, 49.3876}},
			door{"v_ilev_fibl_door02", {106.38, -742.7, 46.18}},
			door{"v_ilev_fibl_door01", {105.76, -746.65, 46.18}},
			door{"prop_ch3_01_trlrdoor_l", {2333.22998046875, 2574.969970703125, 47.03}},
			door{"prop_ch3_01_trlrdoor_r", {2329.64990234375, 2576.639892578125, 47.03}},
			door{"v_ilev_fh_frntdoor", {0.2169, -1823.3031, 29.63909912109375}},
			door{"v_ilev_bl_doorel_l", {-2053.159912109375, 3239.49, 30.5}},
			door{"v_ilev_bl_doorel_r", {-2054.389892578125, 3237.22998046875, 30.5}},
			door{"prop_cs4_05_tdoor", {31.918, 3666.853515625, 40.8586}},
			door{"prop_magenta_door", {29.102, 3661.4892578125, 40.854698181152344}},
			door{"hei_prop_heist_cutscene_doorc_r", {610.593994140625, -421.8299865722656, 24.979}},
			door{"hei_prop_heist_cutscene_doorc_l", {610.8740234375, -419.364990234375, 24.979}},
			door{"prop_gate_docks_ld", {492.0, -3116.0, 5.0}},
			door{"prop_gate_docks_ld", {476.0, -3116.0, 5.0}},
			door{"prop_fnclink_03gate2", {-687.72998046875, -2458.82, 12.899999999999999}},
			door{"prop_fnclink_03gate2", {-697.82, -1226.5, 12.91}},
			door{"prop_fnclink_03gate2", {-692.77, -2455.929931640625, 12.899999999999999}},
			door{"prop_gate_airport_01", {891.93, -2748.7099609375, 12.95}},
			door{"prop_gate_airport_01", {-896.46, -2746.419921875, 12.95}},
			door{"prop_gate_airport_01", {-859.72998046875, 2683.9, 12.76}},
			door{"prop_facgate_01", {-1019.6099853515625, -1897.02, 13.37}},
			door{"prop_facgate_01", {-160.88, 2636.2, 5.03}},
			door{"prop_facgate_01", {-148.71, 2636.2, 5.03}},
			door{"prop_facgate_01", {237.78, -2936.9599609375, 5.05}},
			door{"prop_gate_docks_ld", {188.28, -2204.610107421875, 9.3}},
			door{"prop_gate_docks_ld", {127.56, -2185.29, 9.3}},
			door{"prop_gate_docks_ld", {-33.22, -2141.27, 9.3}},
			door{"prop_facgate_01", {1000.68, 2454.99, 27.57}},
			door{"prop_facgate_01", {1012.9099731445312, -2456.22998046875, 27.53}},
			door{"prop_facgate_01", {1028.0799560546875, -2364.719970703125, 29.52}},
			door{"prop_facgate_01", {1033.219970703125, -2299.1, 29.52}},
			door{"prop_facgate_01", {1022.4, -2417.1298828125, 28.13}},
			door{"prop_gate_military_01", {2485.43994140625, 432.71, 91.97}},
			door{"prop_gate_prison_01", {2485.09, 335.84, 91.98}},
			door{"prop_facgate_01", {2491.969970703125, -303.48, 91.99}},
			door{"prop_facgate_01", {1944.8599853515625, -957.69, 78.15}},
			door{"prop_facgate_01", {1956.74, -956.8599853515625, 78.15}},
			door{"prop_gate_prison_01", {1845.0, 2604.81, 44.64}},
			door{"prop_gate_prison_01", {1818.55, 2604.81, 44.6}},
			door{"prop_gate_prison_01", {1799.74, 2616.97998046875, 44.61}},
			door{"prop_gate_prison_01", {1813.4, 2488.6298828125, 44.47}},
			door{"prop_gate_prison_01", {1808.8199462890625, 2474.8798828125, 44.47}},
			door{"prop_gate_prison_01", {1762.18994140625, 2426.72998046875, 44.44}},
			door{"prop_gate_prison_01", {1749.219970703125, 2420.28, 44.43}},
			door{"prop_gate_prison_01", {1667.6099853515625, 2408.110107421875, 44.419999999999995}},
			door{"prop_gate_prison_01", {1661.76, 2748.32, 44.43}},
			door{"prop_gate_prison_01", {1653.2099609375, 2409.7099609375, 44.419999999999995}},
			door{"prop_gate_prison_01", {1558.14, 2469.8701171875, 44.4}},
			door{"prop_gate_prison_01", {1551.18, 2482.58, 44.4}},
			door{"prop_gate_prison_01", {1547.41, 2576.6, 44.51}},
			door{"prop_gate_prison_01", {1547.99, 2591.08, 44.51}},
			door{"prop_gate_prison_01", {1576.18994140625, 2667.22998046875, 44.51}},
			door{"prop_gate_prison_01", {1584.63, 2679.02, 44.51}},
			door{"prop_gate_prison_01", {1648.949951171875, 2741.55, 44.45}},
			door{"prop_gate_prison_01", {1762.5799560546875, 2751.9, 44.45}},
			door{"prop_gate_prison_01", {1776.26, 2747.1, 44.43}},
			door{"prop_gate_prison_01", {1829.8, 2702.919921875, 44.45}},
			door{"prop_gate_prison_01", {1834.92, 2689.3701171875, 44.45}},
			door{"prop_fnclink_03gate1", {222.07, 2013.99, 18.41}},
			door{"prop_fnclink_03gate1", {210.92999999999998, -2022.5799560546875, 17.65}},
			door{"prop_facgate_01b", {459.7, -2002.93994140625, 22.07}},
			door{"prop_facgate_01", {451.45, -1994.01, 22.07}},
			door{"prop_facgate_01b", {455.74, -1944.8499755859375, 23.66}},
			door{"prop_facgate_01", {466.76, -1939.65, 23.66}},
			door{"prop_facgate_01b", {539.83, -1901.88, 24.22}},
			door{"prop_facgate_01", {550.87, -1896.75, 24.15}},
			door{"prop_facgate_01", {564.12, -1903.0, 23.71}},
			door{"prop_facgate_01", {567.4, -1908.219970703125, 23.71}},
			door{"prop_fnclink_03gate1", {1081.65, -1818.42, 36.43}},
			door{"prop_facgate_01", {987.52, -1176.8199462890625, 24.55}},
			door{"prop_facgate_01", {705.64, -1319.67, 24.96}},
			door{"prop_facgate_01", {712.95, -1329.42, 24.99}},
			door{"prop_facgate_01", {796.46, 921.49, 24.4}},
			door{"prop_facgate_01", {795.78, -909.33, 24.36}},
			door{"prop_facgate_01", {795.1599731445312, -896.64, 24.1}},
			door{"prop_facgate_01", {794.47998046875, -884.47998046875, 24.06}},
			door{"prop_fnclink_03gate2", {546.1699829101562, -1869.93994140625, 24.53}},
			door{"prop_fnclink_03gate1", {492.3299865722656, -1410.469970703125, 28.43}},
			door{"prop_fnclink_03gate1", {484.57, -1408.5, 28.48}},
			door{"prop_fnclink_03gate1", {469.3299865722656, 1272.6999999999998, 28.82}},
			door{"prop_fnclink_03gate1", {487.87, -1272.5899658203125, 28.86}},
			door{"prop_facgate_08", {488.89, -1011.6699829101562, 27.14}},
			door{"prop_fnclink_03gate1", {527.5499877929688, -1597.3299560546875, 28.39}},
			door{"prop_fnclink_03gate1", {544.94, -1649.75, 27.49}},
			door{"prop_fnclink_03gate2", {151.35, -1668.64, 28.77}},
			door{"prop_fnclink_03gate1", {47.2, -1448.3, 28.44}},
			door{"prop_lrggate_03a", {1876.37, 194.85, 83.33}},
			door{"prop_lrggate_03a", {-1868.31, 183.79, 83.34}},
			door{"prop_lrggate_03a", {-1452.43, 37.03, 51.75}},
			door{"prop_lrggate_03a", {1483.1, 46.93, 53.26}},
			door{"prop_lrggate_03a", {-1507.469970703125, 39.16, 54.41}},
			door{"prop_lrggate_03a", {-1528.3599853515625, 35.77, 55.78}},
			door{"prop_lrggate_02_ld", {-1583.28, 40.14, 59.32}},
			door{"prop_lrggate_02_ld", {-1616.22998046875, 79.78, 60.78}},
			door{"prop_lrggate_03a", {-924.97998046875, 9.03, 43.28}},
			door{"prop_lrggate_03a", {-905.7, 14.66, 45.66}},
			door{"prop_lrggate_02_ld", {-844.0499877929688, 155.96, 66.03}},
			door{"prop_lrggate_04a", {-914.32, 184.54, 68.42}},
			door{"v_ilev_trev_doorfront", {-1149.7099609375, -1521.0899658203125, 10.79}},
			door{"v_ilev_ct_door01", {-2343.53, 3265.3701171875, 32.96}},
			door{"v_ilev_ct_door01", {-2342.22998046875, 3267.6201171875, 32.96}},
			door{"v_ilev_housedoor1", {347.8677978515625, -1003.31591796875, -99.09519958496094}},
			door{"v_ilev_mm_door", {257.28961181640625, -1001.2545776367188, -98.85870361328125}},
			door{"v_ilev_mm_doorw", {348.2156982421875, -993.1121826171875, 99.043}},
			door{"v_ilev_fh_bedrmdoor", {-789.3016967773438, 332.01190185546875, 201.55960083}},
			door{"prop_ld_garaged_01", {-815.3281860351562, 185.9571075439453, 72.99}},
			door{"v_ilev_mm_windowwc", {-802.7332763671875, 167.5041046142578, 77.5823974609375}},
			door{"v_ilev_mm_doorm_l", {-816.716, 179.098, 72.84}},
			door{"v_ilev_mm_doorm_r", {-816.1068115234375, 177.51089477539062, 72.8274}},
			door{"prop_bh1_48_backdoor_l", {-796.565673828125, 177.22140502929688, 73.04049682617188}},
			door{"prop_bh1_48_backdoor_r", {-794.505126953125, 178.0124053955078, 73.04049682617188}},
			door{"prop_bh1_48_backdoor_l", {-793.394287109375, 180.50750732421875, 73.04049682617188}},
			door{"prop_bh1_48_backdoor_r", {-794.185302734375, 182.5679931640625, 73.04049682617188}},
			door{"v_ilev_mm_door", {-806.2816772460938, 187.02459716796875, 72.624}},
			door{"prop_gate_cult_01_l", {-1041.267578125, 4906.0966796875, 209.2}},
			door{"prop_gate_cult_01_r", {-1044.7490234375, 4914.9716796875, 209.19320678710938}},
			door{"v_ilev_trevtraildr", {1972.7689208984375, 3815.365966796875, 33.663299560546875}},
			door{"v_ilev_fa_frontdoor", {-14.8689, -1441.18212890625, 31.192}},
			door{"v_ilev_ss_door8", {716.7808227539062, -975.4207153320312, 25.057}},
			door{"v_ilev_ss_door7", {719.3817749023438, -975.4185180664062, 25.005699157714844}},
			door{"v_ilev_ss_door02", {710.0, -964.0, 31.0}},
			door{"v_ilev_bl_doorel_l", {3539.0, 3673.7, 20.0}},
			door{"v_ilev_bl_doorel_r", {3541.6, 3673.2, 20.0}},
			door{"v_ilev_store_door", {708.0, -962.0, 31.0}},
			door{"p_jewel_door_l", {-631.9553833, -236.3332977294922, 38.20650100708}},
			door{"p_jewel_door_r1", {-630.426513671875, -238.4375, 38.20650100708}},
			door{"v_ilev_ss_door04", {1395.6134033203125, 3609.326904296875, 35.13079833984375}},
			door{"v_ilev_ss_doorext", {1388.4986572265625, 3614.82763671875, 39.09189987182617}},
			door{"v_ilev_ss_doorext", {1399.6995849609375, 3607.762939453125, 39.09189987182617}},
			door{"prop_com_gar_door_01", {484.564208984375, -1315.573974609375, 30.2033}},
			door{"v_ilev_cs_door", {482.8111877441406, -1311.953, 29.35059928894043}},
			door{"v_ilev_epsstoredoor", {241.3621063232422, 361.0470886230469, 105.00299835205078}},
			door{"v_ilev_fh_frontdoor", {7.5179, 539.526, 176.1781}},
			door{"prop_ch_025c_g_door_01", {18.6504, 546.34, 176.3448028564453}},
			door{"v_ilev_csr_door_l", {-59.893, -1092.9517822265625, 26.8836}},
			door{"v_ilev_csr_door_r", {-60.545799255371094, -1094.7489013671875, 26.8887}},
			door{"v_ilev_csr_door_l", {-38.464, -1108.4461669921875, 26.7198}},
			door{"v_ilev_csr_door_r", {-36.6614990234375, -1109.1015625, 26.7198}},
			door{"v_ilev_rc_door3_l", {-608.7288818359375, -1610.3153076171875, 27.158899307250977}},
			door{"v_ilev_rc_door3_r", {-611.32, -1610.088623046875, 27.158899307250977}},
			door{"v_ilev_rc_door3_l", {-592.9376220703125, -1631.5770263671875, 27.159299850463867}},
			door{"v_ilev_rc_door3_r", {-592.7108764648438, -1628.9859619140625, 27.159299850463867}},
			door{"v_ilev_shrf2door", {-442.66, 6015.2216796875, 31.8663}},
			door{"v_ilev_shrf2door", {-444.4985046386719, 6017.06, 31.8663}},
			door{"v_ilev_shrfdoor", {1855.684814453125, 3683.93017578125, 34.5928}},
			door{"prop_gar_door_01", {-1067.00244140625, -1665.609130859375, 4.7898}},
			door{"prop_gar_door_02", {-1064.76318359375, -1668.7623291015625, 4.8084}},
			door{"prop_gar_door_03_ld", {-1074.648193359375, -1676.13134765625, 4.684}},
			door{"prop_gar_door_05", {201.39999999999998, -153.36520385742188, 57.85219955444336}},
			door{"v_ilev_fb_doorshortl", {-1045.119873046875, -232.00399780273438, 39.4379}},
			door{"v_ilev_fb_doorshortr", {-1046.51611328125, -229.35809326171875, 39.4379}},
			door{"v_ilev_fb_door01", {-1083.6201171875, -260.41668701171875, 38.18669891357422}},
			door{"v_ilev_fb_door02", {-1080.974365234375, -259.0203857421875, 38.18669891357422}},
			door{"v_ilev_gtdoor", {-1042.5699462890625, -240.6, 38.11}},
			door{"v_ilev_roc_door4", {-565.1712036132812, 276.625885, 83.2863}},
			door{"v_ilev_roc_door4", {-561.2863159179688, 293.5043029785156, 87.777099609375}},
			door{"prop_ron_door_01", {1065.2371826171875, -2006.0791015625, 32.2328987121582}},
			door{"prop_ron_door_01", {1083.5472412109375, -1975.4354248046875, 31.622}},
			door{"prop_ron_door_01", {1085.307, -2018.5614013671875, 41.62889862060547}},
			door{"v_ilev_housedoor1", {86.66239929199219, -1959.47705078125, 21.2152}},
			door{"prop_abat_slide", {962.9083862304688, -2105.813720703125, 34.6432}},
			door{"prop_gar_door_04", {778.31, 1867.49, 30.66}},
			door{"prop_ch3_04_door_01l", {2514.32, 317.34, 93.32}},
			door{"prop_ch3_04_door_01r", {2512.419921875, -319.26, 93.32}},
			door{"prop_sc1_12_door", {-58.47, -1530.51, 34.54}},
			door{"prop_ch1_07_door_01l", {-2255.19384765625, 322.2593078613281, 184.92640686035156}},
			door{"prop_ch1_07_door_01r", {-2254.0556640625, 319.7, 184.92640686035156}},
			door{"prop_ch1_07_door_01l", {-2280.596923828125, 265.432, 184.92599487304688}},
			door{"prop_ch1_07_door_01r", {-2278.0390625, 266.57, 184.92599487304688}},
			door{"prop_facgate_08", {413.3648986816406, -1620.0333251953125, 28.3416}},
			door{"prop_facgate_08", {418.28961181640625, -1651.396240234375, 28.29509925842285}},
			door{"prop_facgate_07b", {397.8846130371094, -1607.3837890625, 28.33}},
			door{"prop_sc1_21_g_door_01", {-25.28, -1431.06, 30.84}},
			door{"prop_ss1_14_garage_door", {-62.38, 352.71728515625, 113.2499}},
			door{"prop_motel_door_09", {549.2567138671875, -1773.114990234375, 33.730899810791016}},
			door{"prop_ss1_10_door_l", {-720.39, 256.8599853515625, 80.29}},
			door{"prop_ss1_10_door_r", {-718.4199829101562, 257.79, 80.29}},

			////////////////////////////////////////////////////////////////////

			// Reference from ambient_solomon

			door{"v_ilev_bs_door", {133.0, -1711.0, 29.0}},
			door{"v_ilev_bs_door", {-1287.8568115234375, -1115.7415771484375, 7.1401}},
			door{"v_ilev_bs_door", {1932.9517822265625, 3725.153564453125, 32.9944}},
			door{"v_ilev_bs_door", {1207.8731689453125, -470.06298828125, 66.358}},
			door{"v_ilev_bs_door", {-29.869199752807617, -148.1571044921875, 57.22650146484375}},
			door{"v_ilev_bs_door", {-280.78509521484375, 6232.78173828125, 31.8455}},
			door{"v_ilev_hd_door_l", {-824.0, -187.0, 38.0}},
			door{"v_ilev_hd_door_r", {-823.0, -188.0, 38.0}},
			door{"v_ilev_cs_door01", {82.318603515625, -1392.7518310546875, 29.5261}},
			door{"v_ilev_cs_door01_r", {82.318603515625, -1390.47583, 29.5261}},
			door{"v_ilev_cs_door01", {1686.983154296875, 4821.74072265625, 42.2131}},
			door{"v_ilev_cs_door01_r", {1687.28173828125, 4819.484375, 42.2131}},
			door{"v_ilev_cs_door01", {418.6369934082031, -806.4569702148438, 29.6396}},
			door{"v_ilev_cs_door01_r", {418.6369934082031, -808.7329711914062, 29.6396}},
			door{"v_ilev_cs_door01", {-1096.6612548828125, 2705.4458, 19.25779914855957}},
			door{"v_ilev_cs_door01_r", {-1094.9652099609375, 2706.963623046875, 19.25779914855957}},
			door{"v_ilev_cs_door01", {1196.824951171875, 2703.220947265625, 38.3726}},
			door{"v_ilev_cs_door01_r", {1199.1, 2703.220947265625, 38.3726}},
			door{"v_ilev_cs_door01", {-818.7642211914062, -1079.54443359375, 11.478099822998047}},
			door{"v_ilev_cs_door01_r", {-816.793212890625, -1078.406494140625, 11.478099822998047}},
			door{"v_ilev_cs_door01", {-0.0564, 6517.4609375, 32.027801513671875}},
			door{"v_ilev_cs_door01_r", {1.7253, 6515.91357421875, 32.027801513671875}},
			door{"v_ilev_clothmiddoor", {-1201.4349365234375, -776.8566284179688, 17.9918}},
			door{"v_ilev_clothmiddoor", {617.2457885742188, 2751.022216796875, 42.7578010559082}},
			door{"v_ilev_clothmiddoor", {127.82, -211.827392578125, 55.2275}},
			door{"v_ilev_clothmiddoor", {-3167.75, 1055.5357666015625, 21.532899856567383}},
			door{"v_ilev_ch_glassdoor", {-716.6754150390625, 155.42, 37.6749}},
			door{"v_ilev_ch_glassdoor", {-715.6154174804688, -157.256103515625, 37.6749}},
			door{"v_ilev_ch_glassdoor", {-157.0924072265625, -306.4413146972656, 39.994}},
			door{"v_ilev_ch_glassdoor", {-156.40220642089844, -304.4366149902344, 39.994}},
			door{"v_ilev_ch_glassdoor", {-1454.7818603515625, -231.79269409179688, 50.05649948120117}},
			door{"v_ilev_ch_glassdoor", {-1456.2, -233.36819458, 50.05649948120117}},
			door{"v_ilev_ta_door", {321.81, 178.36, 103.68}},
			door{"v_ilev_ml_door1", {1859.89, 3749.79, 33.18}},
			door{"v_ilev_ml_door1", {-289.1752014160156, 6199.1123046875, 31.637}},
			door{"v_ilev_ta_door", {-1155.4541015625, -1424.0079345703125, 5.0461}},
			door{"v_ilev_ta_door", {1321.28564453125, -1650.5966796875, 52.36629867553711}},
			door{"v_ilev_ta_door", {-3167.788818359375, 1074.766845703125, 20.9209}},
			door{"v_ilev_mm_doorm_l", {-817.0, 179.0, 73.0}},
			door{"v_ilev_mm_doorm_r", {-816.0, 178.0, 73.0}},
			door{"prop_ld_garaged_01", {-815.0, 186.0, 73.0}},
			door{"prop_bh1_48_backdoor_l", {-797.0, 177.0, 73.0}},
			door{"prop_bh1_48_backdoor_r", {-795.0, 178.0, 73.0}},
			door{"prop_bh1_48_backdoor_l", {-793.0, 181.0, 73.0}},
			door{"prop_bh1_48_backdoor_r", {-794.0, 183.0, 73.0}},
			door{"prop_bh1_48_gate_1", {-849.0, 179.0, 70.0}},
			door{"v_ilev_mm_windowwc", {-802.7332763671875, 167.5041046142578, 77.5823974609375}},
			door{"v_ilev_fa_frontdoor", {-14.0, -1441.0, 31.0}},
			door{"v_ilev_fh_frntdoor", {-15.0, -1427.0, 31.0}},
			door{"prop_sc1_21_g_door_01", {-25.28, -1431.06, 30.84}},
			door{"v_ilev_fh_frontdoor", {7.52, 539.53, 176.17999999999998}},
			door{"v_ilev_trevtraildr", {1973.0, 3815.0, 34.0}},
			door{"prop_cs4_10_tr_gd_01", {1972.787353515625, 3824.5537109375, 32.583099365234375}},
			door{"v_ilev_trev_doorfront", {-1150.0, -1521.0, 11.0}},
			door{"prop_com_ls_door_01", {-1145.9, -1991.14, 14.18}},
			door{"prop_id2_11_gdoor", {723.12, -1088.8299560546875, 23.28}},
			door{"prop_com_ls_door_01", {356.09, -134.77, 40.01}},
			door{"v_ilev_carmod3door", {108.8501968383789, 6617.87646484375, 32.673}},
			door{"v_ilev_carmod3door", {114.32060241699219, 6623.22607421875, 32.7160987854}},
			door{"v_ilev_carmod3door", {1182.305419921875, 2645.2421875, 38.806999999999995}},
			door{"v_ilev_carmod3door", {1174.6541748046875, 2645.2421875, 38.68259811401367}},
			door{"v_ilev_janitor_frontdoor", {-107.5401, -9.025799751281738, 70.66960144042969}},
			door{"v_ilev_ss_door8", {717.0, -975.0, 25.0}},
			door{"v_ilev_ss_door7", {719.0, -975.0, 25.0}},
			door{"v_ilev_ss_door02", {709.9813232421875, -963.5311279296875, 30.54529953}},
			door{"v_ilev_ss_door03", {709.9893798828125, -960.66748046875, 30.54529953}},
			door{"v_ilev_store_door", {707.8046264648438, -962.4564208984375, 30.54529953}},
			door{"v_ilev_ml_door1", {1393.0, 3599.0, 35.0}},
			door{"v_ilev_ml_door1", {1395.0, 3600.0, 35.0}},
			door{"v_ilev_ss_door04", {1387.0, 3614.0, 39.0}},
			door{"prop_ron_door_01", {1083.547119140625, -1975.4354248046875, 31.6222}},
			door{"prop_ron_door_01", {1065.237060546875, -2006.0791015625, 32.2328987121582}},
			door{"prop_ron_door_01", {1085.306884765625, -2018.561279296875, 41.62889862060547}},
			door{"v_ilev_bank4door02", {-111.0, 6464.0, 32.0}},
			door{"v_ilev_bank4door01", {-110.0, 6462.0, 32.0}},
			door{"v_ilev_lester_doorfront", {1274.0, -1721.0, 55.0}},
			door{"v_ilev_lester_doorveranda", {1271.89, -1707.5699462890625, 53.79}},
			door{"v_ilev_lester_doorveranda", {1270.77, 1708.1, 53.75}},
			door{"v_ilev_deviantfrontdoor", {-127.5, -1456.18, 37.94}},
			door{"prop_com_gar_door_01", {483.56, -1316.0799560546875, 32.18}},
			door{"v_ilev_cs_door", {483.0, -1312.0, 29.0}},
			door{"prop_strip_door_01", {128.0, -1299.0, 29.0}},
			door{"prop_magenta_door", {96.0, -1285.0, 29.0}},
			door{"prop_motel_door_09", {549.0, -1773.0, 34.0}},
			door{"v_ilev_gangsafedoor", {974.0, -1839.0, 36.0}},
			door{"v_ilev_gangsafedoor", {977.0, -105.0, 75.0}},
			door{"v_ilev_ra_door1_l", {1391.0, 1163.0, 114.0}},
			door{"v_ilev_ra_door1_r", {1391.0, 1161.0, 114.0}},
			door{"prop_cs6_03_door_l", {1396.0, 1143.0, 115.0}},
			door{"prop_cs6_03_door_r", {1396.0, 1141.0, 115.0}},
			door{"v_ilev_ra_door1_l", {1409.0, 1146.0, 114.0}},
			door{"v_ilev_ra_door1_r", {1409.0, 1148.0, 114.0}},
			door{"v_ilev_ra_door1_l", {1408.0, 1159.0, 114.0}},
			door{"v_ilev_ra_door1_r", {1408.0, 1161.0, 114.0}},
			door{"prop_gar_door_01", {-1067.0, -1666.0, 5.0}},
			door{"prop_gar_door_02", {-1065.0, -1669.0, 5.0}},
			door{"prop_map_door_01", {-1104.66, -1638.47998046875, 4.68}},
			door{"v_ilev_fib_door1", {31.72, -1101.8499755859375, 26.57}},
			door{"v_ilev_tort_door", {134.39999999999998, -2204.1, 7.52}},
			door{"v_ilev_bl_shutter2", {3628.0, 3747.0, 28.0}},
			door{"v_ilev_bl_shutter2", {3621.0, 3752.0, 28.0}},
			door{"v_ilev_rc_door3_l", {-608.72998046875, -1610.3199462890625, 27.16}},
			door{"v_ilev_rc_door3_r", {-611.32, -1610.0899658203125, 27.16}},
			door{"v_ilev_rc_door3_l", {-592.94, -1631.5799560546875, 27.16}},
			door{"v_ilev_rc_door3_r", {-592.71, 1628.99, 27.16}},
			door{"v_ilev_ss_door04", {1991.0, 3053.0, 47.0}},
			door{"v_ilev_fh_door4", {1988.3529052734375, 3054.410888671875, 47.3204}},
			door{"prop_epsilon_door_l", {-700.1699829101562, 47.31, 44.3}},
			door{"prop_epsilon_door_r", {-697.94, 48.35, 44.3}},
			door{"v_ilev_epsstoredoor", {241.35740661621094, 361.0487976074219, 105.89630126953125}},
			door{"prop_ch2_09c_garage_door", {-689.1099853515625, 506.97, 110.64}},
			door{"v_ilev_door_orangesolid", {-1055.9599609375, 236.42999999999998, 44.169999999999995}},
			door{"prop_magenta_door", {29.0, 3661.0, 41.0}},
			door{"prop_cs4_05_tdoor", {32.0, 3667.0, 41.0}},
			door{"v_ilev_housedoor1", {87.0, -1959.0, 21.0}},
			door{"v_ilev_fh_frntdoor", {0.0, -1823.0, 30.0}},
			door{"p_cut_door_03", {23.34, 1897.6, 23.05}},
			door{"p_cut_door_02", {524.2, 3081.139892578125, 41.16}},
			door{"v_ilev_po_door", {-1910.5799560546875, -576.01, 19.25}},
			door{"prop_ss1_10_door_l", {-720.39, 256.8599853515625, 80.29}},
			door{"prop_ss1_10_door_r", {-718.4199829101562, 257.79, 80.29}},
			door{"v_ilev_fibl_door02", {106.38, -742.7, 46.18}},
			door{"v_ilev_fibl_door01", {105.76, -746.65, 46.18}},
			door{"v_ilev_ct_door01", {-2343.53, 3265.3701171875, 32.96}},
			door{"v_ilev_ct_door01", {-2342.22998046875, 3267.6201171875, 32.96}},
			door{"ap1_02_door_l", {-1041.9326171875, -2748.16748046875, 22.030799865722656}},
			door{"ap1_02_door_r", {-1044.8408203125, -2746.48876953125, 22.030799865722656}},
			door{"v_ilev_fb_doorshortl", {-1045.119873046875, -232.00399780273438, 39.4379}},
			door{"v_ilev_fb_doorshortr", {-1046.51611328125, -229.35809326171875, 39.4379}},
			door{"v_ilev_fb_door01", {-1083.6201171875, -260.41668701171875, 38.18669891357422}},
			door{"v_ilev_fb_door02", {-1080.974365234375, -259.0203857421875, 38.18669891357422}},
			door{"v_ilev_gtdoor", {-1042.5699462890625, -240.6, 38.11}},
			door{"prop_damdoor_01", {1385.2578125, -2079.949462890625, 52.76380157470703}},
			door{"v_ilev_genbankdoor2", {1656.5699462890625, 4849.66015625, 42.35}},
			door{"v_ilev_genbankdoor1", {1656.25, 4852.240234375, 42.35}},
			door{"prop_sec_barrier_ld_01a", {-1051.40185546875, -474.6846923828125, 36.61989974975586}},
			door{"prop_sec_barrier_ld_01a", {-1049.2852783203125, -476.6376037597656, 36.7584}},
			door{"prop_sec_barrier_ld_02a", {-1210.9566650390625, -580.8765258789062, 27.2373}},
			door{"prop_sec_barrier_ld_02a", {-1212.4453125, -578.4401245117188, 27.2373}},
			door{"v_ilev_roc_door4", {-565.1712036132812, 276.625885, 83.2863}},
			door{"v_ilev_roc_door4", {-561.2863159179688, 293.5043029785156, 87.777099609375}},
			door{"p_jewel_door_l", {-631.96, -236.33, 38.21}},
			door{"p_jewel_door_r1", {630.43, -238.44, 38.21}},
			door{"prop_ld_bankdoors_01", {231.62, 216.23, 106.4}},
			door{"prop_ld_bankdoors_01", {232.72, 213.88, 106.4}},
			door{"hei_prop_hei_bankdoor_new", {258.32, 203.84, 106.43}},
			door{"hei_prop_hei_bankdoor_new", {260.76, 202.95, 106.43}},
			door{"hei_v_ilev_bk_gate_pris", {256.31, 220.66, 106.43}},
			door{"v_ilev_bk_door", {266.3599853515625, 217.57, 110.43}},
			door{"v_ilev_shrf2door", {-442.66, 6015.2216796875, 31.8663}},
			door{"v_ilev_shrf2door", {-444.4985046386719, 6017.06, 31.8663}},
			door{"v_ilev_shrfdoor", {1855.684814453125, 3683.93017578125, 34.5928}},
			door{"prop_bhhotel_door_l", {-1223.3499755859375, -172.41, 39.98}},
			door{"prop_bhhotel_door_r", {-1220.93, 173.67999999999998, 39.98}},
			door{"prop_bhhotel_door_l", {1211.99, -190.57, 39.98}},
			door{"prop_bhhotel_door_r", {-1213.26, 192.98, 39.98}},
			door{"prop_bhhotel_door_l", {-1217.77, 201.54, 39.98}},
			door{"prop_bhhotel_door_r", {-1219.04, 203.95, 39.98}},
			door{"prop_ch3_04_door_01l", {2514.32, 317.34, 93.32}},
			door{"prop_ch3_04_door_01r", {2512.419921875, -319.26, 93.32}},
			door{"prop_ch3_01_trlrdoor_l", {2333.22998046875, 2574.969970703125, 47.03}},
			door{"prop_ch3_01_trlrdoor_r", {2329.64990234375, 2576.639892578125, 47.03}},
			door{"v_ilev_gc_door04", {16.127899169921875, -1114.60546875, 29.9468994140625}},
			door{"v_ilev_gc_door03", {18.57200050354, -1115.4951171875, 29.9468994140625}},
			door{"v_ilev_gc_door04", {1698.17626953125, 3751.505615234375, 34.8553}},
			door{"v_ilev_gc_door03", {1699.9371337890625, 3753.420166015625, 34.8553}},
			door{"v_ilev_gc_door04", {244.72740173339844, -44.0791015625, 70.91}},
			door{"v_ilev_gc_door03", {243.83790588378906, -46.5232, 70.91}},
			door{"v_ilev_gc_door04", {845.3624267578125, -1024.5390625, 28.3448}},
			door{"v_ilev_gc_door03", {842.7683715820312, -1024.5390625, 23.3448}},
			door{"v_ilev_gc_door04", {-326.1122131347656, 6075.26953125, 31.6047000885}},
			door{"v_ilev_gc_door03", {-324.27301025390625, 6077.10888671875, 31.6047000885}},
			door{"v_ilev_gc_door04", {-665.2423706054688, -944.3256225585938, 21.9792}},
			door{"v_ilev_gc_door03", {-662.6414184570312, -944.3256225585938, 21.9792}},
			door{"v_ilev_gc_door04", {-1313.825927734375, -389.125885, 36.845699310302734}},
			door{"v_ilev_gc_door03", {-1314.4649658203125, -391.6471862792969, 36.845699310302734}},
			door{"v_ilev_gc_door04", {-1114.0089111328125, 2689.77, 18.704099655151367}},
			door{"v_ilev_gc_door03", {-1112.0708, 2691.504638671875, 18.704099655151367}},
			door{"v_ilev_gc_door04", {-3164.84521484375, 1081.3917236328125, 20.9887}},
			door{"v_ilev_gc_door03", {-3163.8115234375, 1083.7784423828125, 20.9887}},
			door{"v_ilev_gc_door04", {2570.904541015625, 303.3555908203125, 108.88480377197266}},
			door{"v_ilev_gc_door03", {2568.3037109375, 303.3555908203125, 108.88480377197266}},
			door{"v_ilev_gc_door04", {813.1779174804688, -2148.26953125, 29.7689}},
			door{"v_ilev_gc_door03", {810.576904296875, -2148.26953125, 29.7689}},
			door{"v_ilev_gc_door01", {6.8179, -1098.20947265625, 29.9468994140625}},
			door{"v_ilev_gc_door01", {827.5341796875, -2160.49267578125, 29.7688}},
			door{"prop_lrggate_01c_l", {-1107.01, 289.38, 64.76}},
			door{"prop_lrggate_01c_r", {1101.62, 290.3599853515625, 64.76}},
			door{"prop_lrggate_01c_l", {-1138.64, 300.82, 67.18}},
			door{"prop_lrggate_01c_r", {-1137.05, 295.59, 67.18}},
			door{"v_ilev_bl_doorel_l", {-2053.159912109375, 3239.49, 30.5}},
			door{"v_ilev_bl_doorel_r", {-2054.389892578125, 3237.22998046875, 30.5}},
			door{"v_ilev_cbankcountdoor01", {-108.91, 6469.10986328125, 31.91}},
			door{"prop_fnclink_03gate5", {-182.91, 6168.3701171875, 32.14}},
			door{"v_ilev_csr_door_l", {59.89, -1092.949951171875, 26.88}},
			door{"v_ilev_csr_door_r", {60.55, -1094.75, 26.89}},
			door{"v_ilev_csr_door_l", {-39.13, -1108.219970703125, 26.72}},
			door{"v_ilev_csr_door_r", {-37.33, 1108.87, 26.72}},
			door{"prop_ron_door_01", {1943.72998046875, 3803.6298828125, 32.31}},
			door{"v_ilev_genbankdoor2", {316.39, 276.49, 54.52}},
			door{"v_ilev_genbankdoor1", {313.96, -275.6, 54.52}},
			door{"v_ilev_genbankdoor2", {-2965.7099609375, 484.22, 16.05}},
			door{"v_ilev_genbankdoor1", {-2965.82, 481.63, 16.05}},
			door{"v_ilev_abbmaindoor", {962.1, -2183.83, 31.06}},
			door{"v_ilev_abbmaindoor2", {961.7899780273438, -2187.08, 31.06}},
			door{"prop_ch3_04_door_02", {2508.429931640625, -336.63, 115.76}},
			door{"prop_ch1_07_door_01l", {-2255.18994140625, 322.26, 184.92999999999998}},
			door{"prop_ch1_07_door_01r", {-2254.06, 319.7, 184.92999999999998}},
			door{"prop_ch1_07_door_01l", {-2301.1298828125, 336.91, 184.92999999999998}},
			door{"prop_ch1_07_door_01r", {-2298.57, 338.04998779296875, 184.92999999999998}},
			door{"prop_ch1_07_door_01l", {-2222.32, 305.8599853515625, 184.92999999999998}},
			door{"prop_ch1_07_door_01r", {-2221.18994140625, 303.3, 184.92999999999998}},
			door{"prop_ch1_07_door_01l", {-2280.6, 265.43, 184.92999999999998}},
			door{"prop_ch1_07_door_01r", {-2278.04, 266.57, 184.92999999999998}},
			door{"prop_gar_door_04", {778.31, 1867.49, 30.66}},
			door{"prop_gate_tep_01_l", {-721.3499755859375, 91.01, 56.68}},
			door{"prop_gate_tep_01_r", {-728.84, 88.64, 56.68}},
			door{"prop_artgallery_02_dr", {-2287.6201171875, 363.9, 174.92999999999998}},
			door{"prop_artgallery_02_dl", {-2289.78, 362.91, 174.92999999999998}},
			door{"prop_artgallery_02_dr", {-2289.860107421875, 362.88, 174.92999999999998}},
			door{"prop_artgallery_02_dl", {-2292.01, 361.89, 174.92999999999998}},
			door{"prop_fnclink_07gate1", {1803.93994140625, 3929.01, 33.72}},
			door{"v_ilev_genbankdoor2", {348.81, 47.26, 49.39}},
			door{"v_ilev_genbankdoor1", {-351.26, 46.41, 49.39}},
			door{"prop_abat_slide", {962.9083862304688, -2105.813720703125, 34.6432}}
		};

		vector3 load_ilp(ilp i, bool toggle) {
			switch (i) {
				case ilp::bahama_mamas:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1388.0013427734375, -618.419677734375, 30.819599151611328), false);
						ntv::STREAMING::REQUEST_IPL("v_bahama");
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1388.0013427734375, -618.419677734375, 30.819599151611328), true);
						ntv::STREAMING::REMOVE_IPL("v_bahama");
					}
					return {-1388.0013427734375, -618.419677734375, 30.819599151611328};

				case ilp::chopshop: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(479.0567932128906f, -1316.8253173828125f, 28.2038f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_chopshop");
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						//ntv::OBJECT::_DOOR_CONTROL(-664582244, 482.8112f, -1311.953f, 29.35057f, true, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-190780785, 484.5652f, -1315.574f, 30.20331f, true, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_chopshop");
					}
					return {484.5652f, -1315.574f, 30.20331f};
				}

				case ilp::cluckin_bell:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission1");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission2");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission3");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission4");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_offmission");
					} else {
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission1");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission2");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission3");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission4");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_offmission");
					}
					return {0, 0, 0};

				case ilp::comedy_club:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-447.4833068847656, 280.3197021484375, 77.52149963378906), false);
						ntv::STREAMING::REQUEST_IPL("v_comedy");
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-447.4833068847656, 280.3197021484375, 77.52149963378906), true);
						ntv::STREAMING::REMOVE_IPL("v_comedy");
					}
					return {-447.4833068847656, 280.3197021484375, 77.52149963378906};

				case ilp::fame_or_shame_stadium:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("sp1_10_fake_interior");
						ntv::STREAMING::REMOVE_IPL("sp1_10_fake_interior_lod");
						ntv::STREAMING::REQUEST_IPL("sp1_10_real_interior");
						ntv::STREAMING::REQUEST_IPL("sp1_10_real_interior_lod");
					} else {
						ntv::STREAMING::REMOVE_IPL("sp1_10_real_interior");
						ntv::STREAMING::REMOVE_IPL("sp1_10_real_interior_lod");
						ntv::STREAMING::REQUEST_IPL("sp1_10_fake_interior");
						ntv::STREAMING::REQUEST_IPL("sp1_10_fake_interior_lod");
					}
					return {0, 0, 0};

				case ilp::fib_lobby:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("FIBlobby");
						ntv::STREAMING::REMOVE_IPL("FIBlobbyfake");
						//ntv::OBJECT::_DOOR_CONTROL(-1517873911, 106.3793f, -742.6982f, 46.51962f, false, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-90456267, 105.7607f, -746.646f, 46.18266f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::STREAMING::REQUEST_IPL("FIBlobbyfake");
						ntv::STREAMING::REMOVE_IPL("FIBlobby");
						//ntv::OBJECT::_DOOR_CONTROL(-1517873911, 106.3793f, -742.6982f, 46.51962f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-90456267, 105.7607f, -746.646f, 46.18266f, true, 0.0f, 0.0f, 0.0f);
					}
					return {105.7607f, -746.646f, 46.18266f};

				case ilp::foundry: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1087.1951904296875, -1988.4449462890625, 28.649);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_foundry");
						//ntv::OBJECT::_DOOR_CONTROL(-1428622127, 1083.547f, -1975.435f, 31.62222f, true, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1428622127, 1085.307f, -2018.561f, 41.62894f, true, 0.0f, 0.0f, 1.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_foundry");
					}
					return {1085.307f, -2018.561f, 41.62894f};
				}

				case ilp::floyds_house:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("vb_30_crimetape");
						//ntv::OBJECT::_DOOR_CONTROL(-607040053, -1149.709f, -1521.088f, 10.78267f, false, 0.0f, 0.0f, 0.0f);
					}
					return {-1149.709f, -1521.088f, 10.78267f};

				case ilp::epsilon: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(245.15640258789062, 370.21099853515625, 104.73819732666016);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_epsilonism");
						//ntv::OBJECT::_DOOR_CONTROL(-1230442770, 241.3621f, 361.0471f, 105.8883f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_epsilonism");
						//ntv::OBJECT::_DOOR_CONTROL(-1230442770, 241.3621f, 361.0471f, 105.8883f, true, 0.0f, 0.0f, 0.0f);
					}
					return {241.3621f, 361.0471f, 105.8883f};
				}

				case ilp::hospital_normal:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("RC12B_Destroyed");
						ntv::STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
						ntv::STREAMING::REMOVE_IPL("RC12B_Default");
						ntv::STREAMING::REMOVE_IPL("RC12B_Fixed");
						ntv::STREAMING::REQUEST_IPL("RC12B_Default");//state 1 normal
					}
					return {0, 0, 0};

				case ilp::hospital_destroyed:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("RC12B_Destroyed");
						ntv::STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
						ntv::STREAMING::REMOVE_IPL("RC12B_Default");
						ntv::STREAMING::REMOVE_IPL("RC12B_Fixed");
						ntv::STREAMING::REQUEST_IPL("RC12B_Destroyed");//state 3 1of2
						ntv::STREAMING::REQUEST_IPL("RC12B_HospitalInterior");//state 3 2of2 Destroyed Interior
					}
					return {0, 0, 0};

				case ilp::hospital_boarded_up:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("RC12B_Destroyed");
						ntv::STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
						ntv::STREAMING::REMOVE_IPL("RC12B_Default");
						ntv::STREAMING::REMOVE_IPL("RC12B_Fixed");
						ntv::STREAMING::REQUEST_IPL("RC12B_Fixed");//state 2 boarded up
					}
					return {0, 0, 0};

				case ilp::janitor:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("v_janitor");
						//ntv::OBJECT::_DOOR_CONTROL(486670049, -107.5373f, -9.018099f, 70.67085f, false, 0.0f, 0.0f, 0.0f);
					}
					return {-107.5373f, -9.018099f, 70.67085f};

				case ilp::jewel_store:
					if (toggle) {
						auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-630.4, -236.7, 40.0);
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("post_hiest_unload");
						ntv::STREAMING::REMOVE_IPL("jewel2fake");
						ntv::STREAMING::REMOVE_IPL("bh1_16_refurb");
						//ntv::OBJECT::_DOOR_CONTROL(9467943, -630.4265f, -238.4375f, 38.20653f, true, 0.0f, 0.0f, 1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1425919976, -631.9554f, -236.3333f, 38.20653f, true, 0.0f, 0.0f, -1.0f);
					}
					return {-631.9554f, -236.3333f, 38.20653f};

				case ilp::lab:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(3522.84521484375, 3707.96533203125, 19.9918), false);
						ntv::STREAMING::REQUEST_IPL("v_lab");
						//ntv::OBJECT::_DOOR_CONTROL(-1081024910, 3620.843f, 3751.527f, 27.69009f, false, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1081024910, 3627.713f, 3746.716f, 27.69009f, false, 0.0f, 0.0f, -1.0f);
						//elevator coords 3540.65f, 3675.77f, 28.12f
						//elevator2 coords 3540.65f, 3675.77f, 20.12f
					}
					return {3627.713f, 3746.716f, 27.69009f};

				case ilp::life_invader:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("facelobby");  // lifeinvader
						ntv::STREAMING::REMOVE_IPL("facelobbyfake");
						//ntv::OBJECT::_DOOR_CONTROL(-340230128, -1042.518, -240.6915, 38.11796, true, 0.0f, 0.0f, -1.0f);
					} else {
						ntv::STREAMING::REMOVE_IPL("facelobby");  // lifeinvader
						ntv::STREAMING::REQUEST_IPL("facelobbyfake");
						//ntv::OBJECT::_DOOR_CONTROL(-340230128, -1042.518, -240.6915, 38.11796, true, 0.0f, 0.0f, 0.0f);
					}
					return {-1042.518, -240.6915, 38.11796};

				case ilp::Lesters_house:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1274.933837890625, -1714.7255859375, 53.77149963378906), false);
						ntv::STREAMING::REQUEST_IPL("v_lesters");
						//ntv::OBJECT::_DOOR_CONTROL(1145337974, 1273.816f, -1720.697f, 54.92143f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1274.933837890625, -1714.7255859375, 53.77149963378906), false);
						ntv::STREAMING::REMOVE_IPL("v_lesters");
						//ntv::OBJECT::_DOOR_CONTROL(1145337974, 1273.816f, -1720.697f, 54.92143f, true, 0.0f, 0.0f, 0.0f);
					}
					return {1273.816f, -1720.697f, 54.92143f};

				case ilp::lesters_factory:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REMOVE_IPL("id2_14_during1");
						ntv::STREAMING::REMOVE_IPL("id2_14_during2");
						ntv::STREAMING::REMOVE_IPL("id2_14_on_fire");
						ntv::STREAMING::REMOVE_IPL("id2_14_post_no_int");
						ntv::STREAMING::REMOVE_IPL("id2_14_pre_no_int");
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REQUEST_IPL("id2_14_during1");
						//ntv::OBJECT::_DOOR_CONTROL(826072862, 717.0f, -975.0f, 25.0f, false, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(763780711, 719.0f, -975.0f, 25.0f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REMOVE_IPL("id2_14_during1");
						ntv::STREAMING::REMOVE_IPL("id2_14_during2");
						ntv::STREAMING::REMOVE_IPL("id2_14_on_fire");
						ntv::STREAMING::REMOVE_IPL("id2_14_post_no_int");
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REQUEST_IPL("id2_14_post_no_int");
					}
					return {719.0f, -975.0f, 25.0f};

				case ilp::morgue:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-447.4833068847656, 280.3197021484375, 77.52149963378906), false);
						ntv::STREAMING::REQUEST_IPL("Coroner_Int_on");
						ntv::STREAMING::REMOVE_IPL("Coroner_Int_off");
						//teleport coords 275.1f,  -1360.6f,  24.5f
						//teleport2 coords 240.8f, -1379.5f, 33.74f
					}
					return {-447.4833068847656, 280.3197021484375, 77.52149963378906};

				case ilp::o_neil_ranch:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("farm_burnt");
						ntv::STREAMING::REMOVE_IPL("farm_burnt_lod");
						ntv::STREAMING::REMOVE_IPL("farm_burnt_props");
						ntv::STREAMING::REMOVE_IPL("farmint_cap");
						ntv::STREAMING::REMOVE_IPL("farmint_cap_lod");
						ntv::STREAMING::REQUEST_IPL("farm");
						ntv::STREAMING::REQUEST_IPL("farmint");
						ntv::STREAMING::REQUEST_IPL("farm_lod");
						ntv::STREAMING::REQUEST_IPL("farm_props");
					} else {
						ntv::STREAMING::REMOVE_IPL("farm");
						ntv::STREAMING::REMOVE_IPL("farmint");
						ntv::STREAMING::REMOVE_IPL("farm_lod");
						ntv::STREAMING::REMOVE_IPL("farm_props");
						ntv::STREAMING::REQUEST_IPL("farm_burnt");
						ntv::STREAMING::REQUEST_IPL("farm_burnt_lod");
						ntv::STREAMING::REQUEST_IPL("farm_burnt_props");
						ntv::STREAMING::REQUEST_IPL("farmint_cap");
						ntv::STREAMING::REQUEST_IPL("farmint_cap_lod");
					}
					return {0, 0, 0};

				case ilp::psycheoffice:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1906.7857666015625, -573.7576293945312, 19.077299118041992), false);
						ntv::STREAMING::REQUEST_IPL("v_psycheoffice");
					}
					return {-1906.7857666015625, -573.7576293945312, 19.077299118041992};

				case ilp::ranch: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1399.9730224609375, 1148.755859375, 113.33360290527344);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::INTERIOR::_LOAD_INTERIOR(intr);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						////ntv::OBJECT::_DOOR_CONTROL(1504256620, 1395.92f, 1142.904f, 114.7902f, true, 0.0f, 0.0f, 1.0f);
						////ntv::OBJECT::_DOOR_CONTROL(-52575179, 1390.666f, 1133.317f, 114.4808f, true, 0.0f, 0.0f, -1.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
					}
					return {1399.9730224609375, 1148.755859375, 113.33360290527344};
				}

				case ilp::rogers_salvage_and_scrap: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-598.6378784179688, -1608.3985595703125, 26.010799407958984);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_recycle");
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -608.7289f, -1610.315f, 27.15894f, false, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -611.32f, -1610.089f, 27.15894f, false, 0.0f, 0.0f, 1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -592.9376f, -1631.577f, 27.15931f, false, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -592.7109f, -1628.986f, 27.15931f, false, 0.0f, 0.0f, 1.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_recycle");
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -608.7289f, -1610.315f, 27.15894f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -611.32f, -1610.089f, 27.15894f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -592.9376f, -1631.577f, 27.15931f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -592.7109f, -1628.986f, 27.15931f, true, 0.0f, 0.0f, 0.0f);
					}
					return {-592.7109f, -1628.986f, 27.15931f};
				}

				case ilp::sheriff_office_paleto:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-444.89068603515625, 6013.5869140625, 30.7164), false);
						ntv::INTERIOR::CAP_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-444.89068603515625, 6013.5869140625, 30.7164), false);
						ntv::STREAMING::REQUEST_IPL("v_sheriff2");
						ntv::STREAMING::REMOVE_IPL("cs1_16_sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -444.4985f, 6017.06f, 31.86633f, false, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -442.66f, 6015.222f, 31.86633f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-444.89068603515625, 6013.5869140625, 30.7164), true);
						ntv::STREAMING::REMOVE_IPL("v_sheriff2");
						ntv::STREAMING::REQUEST_IPL("cs1_16_sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -444.4985f, 6017.06f, 31.86633f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -442.66f, 6015.222f, 31.86633f, true, 0.0f, 0.0f, 0.0f);
					}
					return {-442.66f, 6015.222f, 31.86633f};

				case ilp::sheriff_office_sandy_shores: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1854.2537841796875, 3686.738525390625, 33.2671012878418);
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_sheriff");
						ntv::STREAMING::REMOVE_IPL("sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1765048490, 1855.685f, 3683.93f, 34.59282f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_sheriff");
						ntv::STREAMING::REQUEST_IPL("sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1765048490, 1855.685f, 3683.93f, 34.59282f, true, 0.0f, 0.0f, 0.0f);
					}
					return {1855.685f, 3683.93f, 34.59282f};
				}

				case ilp::simeons_showroom:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("v_carshowroom");
						ntv::STREAMING::REMOVE_IPL("shutter_open");
						ntv::STREAMING::REMOVE_IPL("shutter_closed");
						ntv::STREAMING::REMOVE_IPL("shr_int");
						ntv::STREAMING::REMOVE_IPL("csr_inMission");
						ntv::STREAMING::REMOVE_IPL("fakeint");
						ntv::STREAMING::REQUEST_IPL("shr_int");
					} else {
						ntv::STREAMING::REMOVE_IPL("v_carshowroom");
						ntv::STREAMING::REMOVE_IPL("shutter_open");
						ntv::STREAMING::REMOVE_IPL("shutter_closed");
						ntv::STREAMING::REMOVE_IPL("shr_int");
						ntv::STREAMING::REMOVE_IPL("csr_inMission");
						ntv::STREAMING::REMOVE_IPL("fakeint");
						ntv::STREAMING::REQUEST_IPL("fakeint");
					}
					return {0, 0, 0};

				case ilp::slaughter_house: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(982.2329711914062, -2160.381591796875, 28.4761);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_abattoir");
						//ntv::OBJECT::_DOOR_CONTROL(-1468417022, 962.9084f, -2105.813f, 32.52716f, true, 0.0f, 0.0f, 1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1755793225, 962.0066f, -2183.816f, 31.06194f, true, 0.0f, 0.0f, 1.0f);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						//ntv::OBJECT::_DOOR_CONTROL(-1468417022, 962.9084f, -2105.813f, 32.52716f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1755793225, 962.0066f, -2183.816f, 31.06194f, true, 0.0f, 0.0f, 0.0f);
						ntv::STREAMING::REMOVE_IPL("v_abattoir");
					}
					return {962.0066f, -2183.816f, 31.06194f};
				}

				case ilp::solomons_office:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1005.663208f, -478.3460998535156f, 49.0265f), false);
						ntv::STREAMING::REQUEST_IPL("v_58_sol_office");
					}
					return {-1005.663208f, -478.3460998535156f, 49.0265f};

				case ilp::stab_city:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REMOVE_IPL("des_methtrailer");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp1");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp2");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp3");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkA_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkB_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkC_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkD_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkE_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("methtrailer_grp1");
					}
					return {0, 0, 0};

				case ilp::stab_city_burnt:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REMOVE_IPL("des_methtrailer");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp1");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp2");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp3");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkA_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkB_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkC_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkD_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkE_grp2");
						ntv::STREAMING::REQUEST_IPL("des_methtrailer");
						ntv::STREAMING::REQUEST_IPL("methtrailer_grp3");
					}
					return {0, 0, 0};

				case ilp::stab_city_on_fire:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REMOVE_IPL("des_methtrailer");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp1");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp2");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp3");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkA_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkB_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkC_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkD_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkE_grp2");
						ntv::STREAMING::REQUEST_IPL("des_methtrailer");
						ntv::STREAMING::REQUEST_IPL("methtrailer_grp2");
					}
					return {0, 0, 0};

				case ilp::trevors_trailer:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("TrevorsTrailerTrash");
						ntv::STREAMING::REMOVE_IPL("TrevorsTrailerTidy");
						ntv::STREAMING::REMOVE_IPL("TrevorsTrailer");
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1973.0, 3815.0, 34.0), false);
						ntv::STREAMING::REQUEST_IPL("TrevorsTrailerTidy");
						//ntv::OBJECT::_DOOR_CONTROL(132154435, 1972.769f, 3815.366f, 33.66326f, false, 0.0f, 0.0f, 0.0f);
					}
					return {1972.769f, 3815.366f, 33.66326f};

				case ilp::tequl_la_la: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-556.5089111328125, 286.318115234375, 81.1763);
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_rockclub");
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -565.1712f, 276.6259f, 83.28626f, false, 0.0f, 0.0f, 0.0f);// front door
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -561.2866f, 293.5044f, 87.77851f, false, 0.0f, 0.0f, 0.0f);// back door
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_rockclub");
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -565.1712f, 276.6259f, 83.28626f, true, 0.0f, 0.0f, 0.0f);// front door
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -561.2866f, 293.5044f, 87.77851f, true, 0.0f, 0.0f, 0.0f);// back door
					}
					return {-561.2866f, 293.5044f, 87.77851f};
				}

				case ilp::torture:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(147.43299865722656, -2201.370361328125, 3.688), false);
						ntv::STREAMING::REQUEST_IPL("v_torture");
						//ntv::OBJECT::_DOOR_CONTROL(464151082, 134.3954f, -2204.097f, 7.514325f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(147.43299865722656, -2201.370361328125, 3.688), false);
						ntv::STREAMING::REMOVE_IPL("v_torture");
						//ntv::OBJECT::_DOOR_CONTROL(464151082, 134.3954f, -2204.097f, 7.514325f, true, 0.0f, 0.0f, 0.0f);
					}
					return {134.3954f, -2204.097f, 7.514325f};

				case ilp::mp_lost_safe_house:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("hei_bi_hw1_13_door");
						ntv::STREAMING::REQUEST_IPL("bkr_bi_hw1_13_int");
					}
					return {984.1552f, -95.3662f, 75.9326f};

				case ilp::mp_yacht:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
					}
					return {-2062.79f, -1025.98f, 3.06146f};

				case ilp::mp_heist_carrier:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("hei_carrier");
						ntv::STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int1");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int2");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int3");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int4");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int5");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int6");
						ntv::STREAMING::REQUEST_IPL("hei_carrier_LODLights");
					}
					return {3068.94f, -4721.21f, 15.2614f};
			}
			return {0.0f, 0.0f, 0.0f};
		}
	} /* world */
} /* nob */
