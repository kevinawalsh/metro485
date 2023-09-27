{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 5,
			"revision" : 5,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 34.0, 87.0, 1087.0, 779.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-74",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 558.999997019767761, 833.0, 168.0, 22.0 ],
					"text" : "set 168 1 2 3 1 2 3 1 2 3 1 2 3"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 537.166677117347717, 809.0, 168.0, 22.0 ],
					"text" : "set 252 1 2 1 2 1 2 1 2 1 2 1 2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 573.999997019767761, 862.0, 208.0, 22.0 ],
					"text" : "set 126 1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-56",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 5,
					"outlettype" : [ "bang", "bang", "bang", "bang", "" ],
					"patching_rect" : [ 487.0, 775.0, 64.0, 22.0 ],
					"text" : "sel 0 1 2 3"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 14.0,
					"id" : "obj-55",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 332.006082765758038, 688.333330273628235, 183.0, 69.0 ],
					"text" : "2 div (16 = 8 bars x 2 ticks)\n3 div (12 = 4 bars x 3 ticks)\n4 div (16 = 4 bars x 4 ticks)\n6 div (12 = 2 bars x 6 ticks)",
					"textcolor" : [ 0.03921568627451, 0.843137254901961, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activecolor" : [ 0.090196078431373, 0.894117647058824, 1.0, 1.0 ],
					"disabled" : [ 0, 0, 0, 0 ],
					"id" : "obj-53",
					"itemtype" : 0,
					"maxclass" : "radiogroup",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 319.499998509883881, 689.333330273628235, 195.506084255874157, 66.0 ],
					"size" : 4,
					"value" : 2
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 492.999997019767761, 918.666669726371765, 113.0, 22.0 ],
					"text" : "s arduinoConductor"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 61.666674137115479, 775.0, 111.0, 22.0 ],
					"text" : "r arduinoConductor"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 587.666677117347717, 890.0, 161.0, 22.0 ],
					"text" : "set 84 1 2 3 4 5 6 1 2 3 4 5 6"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 18.0,
					"id" : "obj-8",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 592.0, 281.5, 140.0, 27.0 ],
					"text" : "Player Controls"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-153",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 208.333325117826462, 911.821428239345551, 213.0, 22.0 ],
					"text" : "send goto mambo no 5 at time 1.5 sec"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-141",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1337.749987185001373, 669.333330273628235, 85.0, 22.0 ],
					"text" : "r arduino_msg"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgcolor2" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgfillcolor_angle" : 270.0,
					"bgfillcolor_autogradient" : 0.0,
					"bgfillcolor_color" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgfillcolor_color1" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
					"bgfillcolor_proportion" : 0.5,
					"bgfillcolor_type" : "color",
					"fontsize" : 36.0,
					"gradient" : 1,
					"id" : "obj-140",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 573.523815751075745, 631.690472602844238, 745.0, 49.0 ],
					"text" : "twinkle twinkle 42 teapots 3.14 cupcakes"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgcolor2" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgfillcolor_angle" : 270.0,
					"bgfillcolor_autogradient" : 0.0,
					"bgfillcolor_color" : [ 0.082352941176471, 0.890196078431372, 0.380392156862745, 1.0 ],
					"bgfillcolor_color1" : [ 0.854901960784314, 0.082352941176471, 0.890196078431372, 1.0 ],
					"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
					"bgfillcolor_proportion" : 0.5,
					"bgfillcolor_type" : "color",
					"fontsize" : 36.0,
					"gradient" : 1,
					"id" : "obj-138",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 574.333312153816223, 688.333330273628235, 745.0, 49.0 ],
					"text" : "elapsed 8 maxmsp ticks since previous"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-137",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1359.083311140537262, 717.821427404880524, 223.0, 22.0 ],
					"text" : "elapsed $1 maxmsp ticks since previous"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-135",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1364.166674137115479, 499.333335757255554, 92.0, 22.0 ],
					"text" : "r arduino_count"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-134",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1476.0, 497.714285492897034, 81.0, 22.0 ],
					"text" : "r arduino_tick"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-133",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1266.083311140537262, 499.333335757255554, 89.0, 22.0 ],
					"text" : "r arduino_color"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-132",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1317.666677117347717, 322.0, 83.0, 22.0 ],
					"text" : "s arduino_tick"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-127",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1406.666674137115479, 322.0, 87.0, 22.0 ],
					"text" : "s arduino_msg"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-120",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1300.166674137115479, 415.5, 91.0, 22.0 ],
					"text" : "s arduino_color"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-119",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1144.166674137115479, 293.0, 20.5, 22.0 ],
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-116",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1112.666674137115479, 370.5, 61.0, 22.0 ],
					"text" : "17401"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-114",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 4,
					"outlettype" : [ "int", "", "", "int" ],
					"patching_rect" : [ 1112.666674137115479, 336.0, 61.0, 22.0 ],
					"text" : "counter"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-110",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1112.666674137115479, 293.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-108",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"patching_rect" : [ 1300.166674137115479, 293.0, 233.0, 22.0 ],
					"text" : "route tick msg"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-102",
					"linecount" : 9,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1172.999997019767761, 86.0, 406.0, 127.0 ],
					"text" : "Incoming messages.... These messages come from the arduinos.\n\n\"tick 3 7\" -- Tick messages are sent at regular pace. Each contains two numbers: a color and a sequence number. The meter chosen by the conductor defines the pattern of colors received and the length of the sequence.\n\n\"msg twinkle twinkle 42 teapots 3.14 cupcakes\" -- Arbitrary data sent by the conductor, consisting of a list of integers, strings, and floats."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-99",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 815.666674137115479, 413.833335280418396, 52.0, 22.0 ],
					"text" : "debug 1"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"id" : "obj-100",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 874.5, 406.333335280418396, 151.0, 37.0 ],
					"text" : "Enable or disable arduino debug output."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-101",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 751.666674137115479, 413.833335280418396, 52.0, 22.0 ],
					"text" : "debug 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-87",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 961.0, 364.5, 69.0, 22.0 ],
					"text" : "illuminate 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-88",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 915.999998509883881, 364.5, 38.0, 22.0 ],
					"text" : "dim 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-89",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 718.333331108093262, 364.5, 59.0, 22.0 ],
					"text" : "illuminate"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-90",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 684.333331108093262, 364.5, 29.5, 22.0 ],
					"text" : "dim"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"id" : "obj-91",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 821.666674137115479, 310.5, 208.0, 52.0 ],
					"text" : "These take effect when the given seqno comes around again."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-92",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 868.666674137115479, 364.5, 42.0, 22.0 ],
					"text" : "start 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-93",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 821.666674137115479, 364.5, 41.0, 22.0 ],
					"text" : "stop 3"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.956862745098039, 1.0, 0.458823529411765, 1.0 ],
					"bubble" : 1,
					"bubbleside" : 2,
					"bubbleusescolors" : 1,
					"id" : "obj-94",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 595.166677117347717, 310.5, 182.0, 52.0 ],
					"text" : "Main controls.\nThese take effect immediately."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-95",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 634.666674137115479, 364.5, 31.0, 22.0 ],
					"text" : "stop"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-96",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 595.166677117347717, 364.5, 32.0, 22.0 ],
					"text" : "start"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-98",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 611.999997019767761, 466.166669368743896, 135.0, 22.0 ],
					"text" : "udpsend localhost 5557"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-86",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 424.0, 452.333330631256104, 69.0, 22.0 ],
					"text" : "illuminate 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-84",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 378.999998509883881, 452.333330631256104, 38.0, 22.0 ],
					"text" : "dim 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-83",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 182.0, 452.333330631256104, 59.0, 22.0 ],
					"text" : "illuminate"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-81",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 148.0, 452.333330631256104, 29.5, 22.0 ],
					"text" : "dim"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-79",
					"linecount" : 16,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 585.166677117347717, 50.666664719581604, 406.0, 221.0 ],
					"text" : "Player controls.... These messages can be used by individual players to control their own arduino, without affecting other players. Valid messages:\n\nBasics:\n\"start\" -- resume processing tick messages\n\"stop\" -- ignore/mute tick messages\n\"dim\" -- turn off all the LEDs\n\"illuminate\" -- LEDs will follow the pattern defined by the meter\n\nAdvanced:\n\"stop N\" -- ignore/mute ticks when seqno N comes around again\n\"start N\" -- resume processing ticks when seqno N comes around again\n\"illuminate N\" -- illuminate LEDs when seqno N comes around again\n\"dim N\" -- dim LEDs when seqno N comes around again\n\"debug 1\" -- turn on debugging messages\n\"debug 0\" -- turn off debugging messages"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-78",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 257.666674137115479, 782.5, 52.0, 22.0 ],
					"text" : "debug 1"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubblepoint" : 0.0,
					"bubbleside" : 2,
					"id" : "obj-76",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 219.999998509883881, 836.0, 246.000001490116119, 39.0 ],
					"text" : "Send arbitrary data to players, immediately."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-75",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 208.333325117826462, 877.0, 255.0, 22.0 ],
					"text" : "send twinkle twinkle 42 teapots 3.14 cupcakes"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.956862745098039, 1.0, 0.458823529411765, 1.0 ],
					"bubble" : 1,
					"bubbleusescolors" : 1,
					"id" : "obj-72",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 375.499998509883881, 595.666664719581604, 192.000002980232239, 64.0 ],
					"text" : "Define the temp and meter. \nThis takes effect when seqno reaches 1. (Note: if tempo is 0, only the meter is changed.)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-71",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 232.5, 583.666664719581604, 75.0, 22.0 ],
					"text" : "set 0 1 2 3 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-70",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.166666388511658, 647.0, 254.0, 22.0 ],
					"text" : "set 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-65",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 232.5, 616.666664719581604, 138.0, 22.0 ],
					"text" : "set 168 1 2 3 1 2 3 1 2 3"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-62",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.166666388511658, 616.666664719581604, 128.0, 22.0 ],
					"text" : "set 126 1 2 1 2 1 2 3 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 249.666674137115479, 534.0, 48.0, 22.0 ],
					"text" : "set 168"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-54",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 197.0, 534.0, 48.0, 22.0 ],
					"text" : "set 126"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 151.166666388511658, 534.0, 41.0, 22.0 ],
					"text" : "set 84"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.956862745098039, 1.0, 0.458823529411765, 1.0 ],
					"bubble" : 1,
					"bubbleusescolors" : 1,
					"id" : "obj-50",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 369.5, 499.0, 153.0, 64.0 ],
					"text" : "Set the delay between ticks, in milliseconds.\nThis takes effect when seqno reaches 1."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-49",
					"maxclass" : "number",
					"maximum" : 9999,
					"minimum" : 1,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 316.5, 499.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"id" : "obj-47",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 257.666674137115479, 398.333330631256104, 208.0, 52.0 ],
					"text" : "These take effect when the given seqno comes around again."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-46",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 331.666674137115479, 452.333330631256104, 41.0, 22.0 ],
					"text" : "stop 8"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.301960784313725, 0.301960784313725, 0.301960784313725, 1.0 ],
					"bgcolor2" : [ 0.301960784313725, 0.301960784313725, 0.301960784313725, 1.0 ],
					"bgfillcolor_angle" : 270.0,
					"bgfillcolor_autogradient" : 0.0,
					"bgfillcolor_color" : [ 0.776470588235294, 0.0, 0.0, 1.0 ],
					"bgfillcolor_color1" : [ 0.301960784313725, 0.301960784313725, 0.301960784313725, 1.0 ],
					"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
					"bgfillcolor_proportion" : 0.5,
					"bgfillcolor_type" : "color",
					"fontsize" : 24.0,
					"gradient" : 1,
					"id" : "obj-44",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 253.666674137115479, 439.333330631256104, 74.0, 35.0 ],
					"text" : "stop 1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.956862745098039, 1.0, 0.458823529411765, 1.0 ],
					"bubble" : 1,
					"bubbleside" : 2,
					"bubbleusescolors" : 1,
					"id" : "obj-41",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 22.166677117347717, 398.333330631256104, 215.0, 52.0 ],
					"text" : "Main controls.\nThese take effect immediately."
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"id" : "obj-37",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 316.5, 775.0, 151.0, 37.0 ],
					"text" : "Enable or disable arduino debug output."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"linecount" : 27,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 26.0, 10.666664719581604, 406.0, 368.0 ],
					"text" : "Conductor controls.... These messages control the main \"conductor\" arduino, and through that, all of the players too. Valid messages:\n\nBasics:\n\"start\" -- start the metronome ticking\n\"stop\" -- pause the metronome\n\"reset\" -- go back to the start of the meter, i.e. seqno 1\n\"set 126\" -- set the tempo to 126 milliseconds between ticks\n    Note: this only takes effect once the sequence wraps around to 1 again.\n\"set 126 1 2 3 1 2 3\" -- set the tempo, and also define a\n    meter of length 6 with two equal halves that count upwards.\n    The metronome will send, in sequqnece: tick 1 1, tick 2 2,\n    tick 3 3, tick 1 4 tick 2 5, tick 3 6, tick 1 1, tick 2 2, ..., where the first\n    number follows the pattern defined by the meter, and the second\n    number counts from 1 to the meter's length.\n    Note: this only takes effect once the sequence wraps around to 1 again.\n\"dim\" -- turn off all the LEDs\n\"illuminate\" -- LEDs will follow the pattern defined by the meter\n\nAdvanced:\n\"stop N\" -- stop when seqno N comes around again\n\"illuminate N\" -- illuminate LEDs when seqno N comes around again\n\"dim N\" -- dim LEDs when seqno N comes around again\n\"debug 1\" -- turn on debugging messages\n\"debug 0\" -- turn off debugging messages\n\"send hello 3.14 75\" -- send arbitrary strings, floats, and integers to players\n\"set\" -- by itself, with no parameters, this sets tempo and meter to defaults "
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 316.5, 534.0, 41.0, 22.0 ],
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1348.166674137115479, 384.5, 94.0, 22.0 ],
					"text" : "s arduino_count"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.76078431372549, 0.003921568627451, 0.003921568627451, 1.0 ],
					"bgcolor2" : [ 0.76078431372549, 0.003921568627451, 0.003921568627451, 1.0 ],
					"bgfillcolor_angle" : 270.0,
					"bgfillcolor_autogradient" : 0.0,
					"bgfillcolor_color" : [ 0.76078431372549, 0.003921568627451, 0.003921568627451, 1.0 ],
					"bgfillcolor_color1" : [ 0.76078431372549, 0.003921568627451, 0.003921568627451, 1.0 ],
					"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
					"bgfillcolor_proportion" : 0.5,
					"bgfillcolor_type" : "color",
					"gradient" : 1,
					"id" : "obj-18",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 71.666674137115479, 452.333330631256104, 31.0, 22.0 ],
					"text" : "stop"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.301960784313725, 0.301960784313725, 0.301960784313725, 1.0 ],
					"bgcolor2" : [ 0.301960784313725, 0.301960784313725, 0.301960784313725, 1.0 ],
					"bgfillcolor_angle" : 270.0,
					"bgfillcolor_autogradient" : 0.0,
					"bgfillcolor_color" : [ 0.0, 0.592156862745098, 0.392156862745098, 1.0 ],
					"bgfillcolor_color1" : [ 0.301960784313725, 0.301960784313725, 0.301960784313725, 1.0 ],
					"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
					"bgfillcolor_proportion" : 0.5,
					"bgfillcolor_type" : "color",
					"fontsize" : 24.0,
					"gradient" : 1,
					"id" : "obj-16",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 12.666674137115479, 439.333330631256104, 57.0, 35.0 ],
					"text" : "start"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 193.666674137115479, 782.5, 52.0, 22.0 ],
					"text" : "debug 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 109.000002980232239, 452.333330631256104, 35.0, 22.0 ],
					"text" : "reset"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.166666388511658, 583.666664719581604, 128.0, 22.0 ],
					"text" : "set 126 1 2 3 4 1 2 3 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 1172.999997019767761, 293.0, 113.0, 22.0 ],
					"text" : "print arduino says..."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.074509803921569, 0.152941176470588, 1.0, 1.0 ],
					"bgcolor2" : [ 0.074509803921569, 0.152941176470588, 1.0, 1.0 ],
					"bgfillcolor_angle" : 270.0,
					"bgfillcolor_autogradient" : 0.0,
					"bgfillcolor_color" : [ 0.074509803921569, 0.152941176470588, 1.0, 1.0 ],
					"bgfillcolor_color1" : [ 0.074509803921569, 0.152941176470588, 1.0, 1.0 ],
					"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
					"bgfillcolor_proportion" : 0.5,
					"bgfillcolor_type" : "color",
					"fontsize" : 64.0,
					"gradient" : 1,
					"id" : "obj-7",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 575.333312153816223, 549.333330273628235, 745.0, 80.0 ],
					"text" : "tick color 2 count 10"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-68",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 1537.583311140537262, 669.333330273628235, 29.5, 22.0 ],
					"text" : "-"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-67",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1476.0, 530.380950212478638, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-64",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1448.267857283353806, 669.333330273628235, 79.464285433292389, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-60",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1476.0, 564.714285492897034, 32.0, 22.0 ],
					"text" : "ticks"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-57",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "list", "list", "int" ],
					"patching_rect" : [ 1476.0, 592.714285492897034, 40.0, 22.0 ],
					"text" : "date"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-43",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1327.083311140537262, 533.5, 115.0, 22.0 ],
					"text" : "join 2"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-27",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1327.083311140537262, 571.714285492897034, 122.0, 22.0 ],
					"text" : "tick color $1 count $2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 1300.166674137115479, 351.0, 67.0, 22.0 ],
					"text" : "unpack 0 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1172.999997019767761, 220.0, 97.0, 22.0 ],
					"text" : "udpreceive 5556"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 41.999997019767761, 841.0, 135.0, 22.0 ],
					"text" : "udpsend localhost 5557"
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"bgcolor" : [ 1.0, 0.458823529411765, 0.925490196078431, 1.0 ],
					"id" : "obj-3",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 581.166674137115479, 281.5, 459.0, 211.0 ],
					"proportion" : 0.5
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 761.166674137115479, 437.833335280418396, 761.166674137115479, 446.833335280418396, 621.499997019767761, 446.833335280418396 ],
					"source" : [ "obj-101", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-127", 0 ],
					"source" : [ "obj-108", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-132", 0 ],
					"order" : 0,
					"source" : [ "obj-108", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"order" : 1,
					"source" : [ "obj-108", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 101.666666388511658, 677.0, 51.499997019767761, 677.0 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 0 ],
					"source" : [ "obj-110", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-116", 1 ],
					"source" : [ "obj-114", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 3 ],
					"source" : [ "obj-119", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 118.500002980232239, 483.0, 51.499997019767761, 483.0 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 203.166674137115479, 823.0, 198.0, 823.0, 198.0, 822.0, 51.499997019767761, 822.0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"hidden" : 1,
					"source" : [ "obj-133", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"hidden" : 1,
					"source" : [ "obj-134", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 1 ],
					"hidden" : 1,
					"source" : [ "obj-135", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-138", 1 ],
					"hidden" : 1,
					"source" : [ "obj-137", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-140", 1 ],
					"hidden" : 1,
					"source" : [ "obj-141", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 217.833325117826462, 942.678563296794891, 196.107140958309174, 942.678563296794891, 196.107140958309174, 823.928564429283142, 51.499997019767761, 823.928564429283142 ],
					"source" : [ "obj-153", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 22.166674137115479, 482.0, 51.499997019767761, 482.0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 81.166674137115479, 483.0, 51.499997019767761, 483.0 ],
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"hidden" : 1,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 326.0, 562.0, 51.499997019767761, 562.0 ],
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-108", 0 ],
					"order" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-110", 0 ],
					"order" : 2,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"order" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"hidden" : 1,
					"source" : [ "obj-43", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 263.166674137115479, 482.0, 51.499997019767761, 482.0 ],
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 341.166674137115479, 484.0, 51.499997019767761, 484.0 ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"order" : 0,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"midpoints" : [ 326.0, 527.0, 304.0, 527.0, 304.0, 576.0, 242.0, 576.0 ],
					"order" : 1,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-120", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"source" : [ "obj-5", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 160.666666388511658, 557.0, 167.0, 557.0, 51.499997019767761, 557.0 ],
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-56", 0 ],
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 206.5, 563.0, 51.499997019767761, 563.0 ],
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-56", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-59", 0 ],
					"source" : [ "obj-56", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-74", 0 ],
					"source" : [ "obj-56", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-56", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-64", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-57", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 0 ],
					"hidden" : 1,
					"order" : 0,
					"source" : [ "obj-57", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-58", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-59", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-57", 0 ],
					"hidden" : 1,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 259.166674137115479, 562.0, 51.499997019767761, 562.0 ],
					"source" : [ "obj-61", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 101.666666388511658, 679.0, 51.499997019767761, 679.0 ],
					"source" : [ "obj-62", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 1 ],
					"hidden" : 1,
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 242.0, 677.0, 51.499997019767761, 677.0 ],
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-60", 0 ],
					"hidden" : 1,
					"source" : [ "obj-67", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-137", 0 ],
					"hidden" : 1,
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 101.666666388511658, 677.0, 51.499997019767761, 677.0 ],
					"source" : [ "obj-70", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 242.0, 678.0, 51.499997019767761, 678.0 ],
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-74", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 217.833325117826462, 906.0, 196.0, 906.0, 196.0, 820.0, 51.499997019767761, 820.0 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 267.166674137115479, 823.0, 51.499997019767761, 823.0 ],
					"source" : [ "obj-78", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 157.5, 482.0, 51.499997019767761, 482.0 ],
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 191.5, 480.0, 51.499997019767761, 480.0 ],
					"source" : [ "obj-83", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 388.499998509883881, 484.0, 51.499997019767761, 484.0 ],
					"source" : [ "obj-84", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 433.5, 482.0, 51.499997019767761, 482.0 ],
					"source" : [ "obj-86", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 970.5, 396.833335280418396, 621.499997019767761, 396.833335280418396 ],
					"source" : [ "obj-87", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 925.499998509883881, 395.833335280418396, 621.499997019767761, 395.833335280418396 ],
					"source" : [ "obj-88", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 727.833331108093262, 392.166669368743896, 621.499997019767761, 392.166669368743896 ],
					"source" : [ "obj-89", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 693.833331108093262, 394.166669368743896, 621.499997019767761, 394.166669368743896 ],
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 878.166674137115479, 396.166669368743896, 621.499997019767761, 396.166669368743896 ],
					"source" : [ "obj-92", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 831.166674137115479, 394.166669368743896, 621.499997019767761, 394.166669368743896 ],
					"source" : [ "obj-93", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 644.166674137115479, 395.166669368743896, 621.499997019767761, 395.166669368743896 ],
					"source" : [ "obj-95", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 604.666677117347717, 394.166669368743896, 621.499997019767761, 394.166669368743896 ],
					"source" : [ "obj-96", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 825.166674137115479, 445.833335280418396, 621.499997019767761, 445.833335280418396 ],
					"source" : [ "obj-99", 0 ]
				}

			}
 ],
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
