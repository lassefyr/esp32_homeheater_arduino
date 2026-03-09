const char* TEST_JSON_DATA = R"raw([
  {
    "Rank": 23,
    "DateTime": "2025-10-01T00:00:00+03:00",
    "PriceNoTax": 0.04157,
    "PriceWithTax": 0.05217
  },
  {
    "Rank": 24,
    "DateTime": "2025-10-01T00:15:00+03:00",
    "PriceNoTax": 0.04157,
    "PriceWithTax": 0.05217
  },
  {
    "Rank": 25,
    "DateTime": "2025-10-01T00:30:00+03:00",
    "PriceNoTax": 0.04157,
    "PriceWithTax": 0.05217
  },
  {
    "Rank": 26,
    "DateTime": "2025-10-01T00:45:00+03:00",
    "PriceNoTax": 0.04157,
    "PriceWithTax": 0.05217
  },
  {
    "Rank": 20,
    "DateTime": "2025-10-01T01:00:00+03:00",
    "PriceNoTax": 0.03765,
    "PriceWithTax": 0.04725
  },
  {
    "Rank": 19,
    "DateTime": "2025-10-01T01:15:00+03:00",
    "PriceNoTax": 0.034,
    "PriceWithTax": 0.04267
  },
  {
    "Rank": 17,
    "DateTime": "2025-10-01T01:30:00+03:00",
    "PriceNoTax": 0.03265,
    "PriceWithTax": 0.04098
  },
  {
    "Rank": 15,
    "DateTime": "2025-10-01T01:45:00+03:00",
    "PriceNoTax": 0.03242,
    "PriceWithTax": 0.04069
  },
  {
    "Rank": 16,
    "DateTime": "2025-10-01T02:00:00+03:00",
    "PriceNoTax": 0.03243,
    "PriceWithTax": 0.04070
  },
  {
    "Rank": 18,
    "DateTime": "2025-10-01T02:15:00+03:00",
    "PriceNoTax": 0.03274,
    "PriceWithTax": 0.04109
  },
  {
    "Rank": 9,
    "DateTime": "2025-10-01T02:30:00+03:00",
    "PriceNoTax": 0.03113,
    "PriceWithTax": 0.03907
  },
  {
    "Rank": 4,
    "DateTime": "2025-10-01T02:45:00+03:00",
    "PriceNoTax": 0.02695,
    "PriceWithTax": 0.03382
  },
  {
    "Rank": 11,
    "DateTime": "2025-10-01T03:00:00+03:00",
    "PriceNoTax": 0.03229,
    "PriceWithTax": 0.04052
  },
  {
    "Rank": 13,
    "DateTime": "2025-10-01T03:15:00+03:00",
    "PriceNoTax": 0.03231,
    "PriceWithTax": 0.04055
  },
  {
    "Rank": 12,
    "DateTime": "2025-10-01T03:30:00+03:00",
    "PriceNoTax": 0.0323,
    "PriceWithTax": 0.04054
  },
  {
    "Rank": 14,
    "DateTime": "2025-10-01T03:45:00+03:00",
    "PriceNoTax": 0.03239,
    "PriceWithTax": 0.04065
  },
  {
    "Rank": 1,
    "DateTime": "2025-10-01T04:00:00+03:00",
    "PriceNoTax": 0.02182,
    "PriceWithTax": 0.02738
  },
  {
    "Rank": 3,
    "DateTime": "2025-10-01T04:15:00+03:00",
    "PriceNoTax": 0.02599,
    "PriceWithTax": 0.03262
  },
  {
    "Rank": 5,
    "DateTime": "2025-10-01T04:30:00+03:00",
    "PriceNoTax": 0.02749,
    "PriceWithTax": 0.03450
  },
  {
    "Rank": 6,
    "DateTime": "2025-10-01T04:45:00+03:00",
    "PriceNoTax": 0.02756,
    "PriceWithTax": 0.03459
  },
  {
    "Rank": 2,
    "DateTime": "2025-10-01T05:00:00+03:00",
    "PriceNoTax": 0.02201,
    "PriceWithTax": 0.02762
  },
  {
    "Rank": 8,
    "DateTime": "2025-10-01T05:15:00+03:00",
    "PriceNoTax": 0.03093,
    "PriceWithTax": 0.03882
  },
  {
    "Rank": 10,
    "DateTime": "2025-10-01T05:30:00+03:00",
    "PriceNoTax": 0.03115,
    "PriceWithTax": 0.03909
  },
  {
    "Rank": 22,
    "DateTime": "2025-10-01T05:45:00+03:00",
    "PriceNoTax": 0.03857,
    "PriceWithTax": 0.04841
  },
  {
    "Rank": 7,
    "DateTime": "2025-10-01T06:00:00+03:00",
    "PriceNoTax": 0.02811,
    "PriceWithTax": 0.03528
  },
  {
    "Rank": 21,
    "DateTime": "2025-10-01T06:15:00+03:00",
    "PriceNoTax": 0.03817,
    "PriceWithTax": 0.04790
  },
  {
    "Rank": 27,
    "DateTime": "2025-10-01T06:30:00+03:00",
    "PriceNoTax": 0.05521,
    "PriceWithTax": 0.06929
  },
  {
    "Rank": 28,
    "DateTime": "2025-10-01T06:45:00+03:00",
    "PriceNoTax": 0.05612,
    "PriceWithTax": 0.07043
  },
  {
    "Rank": 33,
    "DateTime": "2025-10-01T07:00:00+03:00",
    "PriceNoTax": 0.0691,
    "PriceWithTax": 0.08672
  },
  {
    "Rank": 43,
    "DateTime": "2025-10-01T07:15:00+03:00",
    "PriceNoTax": 0.08251,
    "PriceWithTax": 0.10355
  },
  {
    "Rank": 54,
    "DateTime": "2025-10-01T07:30:00+03:00",
    "PriceNoTax": 0.09347,
    "PriceWithTax": 0.11730
  },
  {
    "Rank": 69,
    "DateTime": "2025-10-01T07:45:00+03:00",
    "PriceNoTax": 0.10654,
    "PriceWithTax": 0.13371
  },
  {
    "Rank": 75,
    "DateTime": "2025-10-01T08:00:00+03:00",
    "PriceNoTax": 0.11743,
    "PriceWithTax": 0.14737
  },
  {
    "Rank": 79,
    "DateTime": "2025-10-01T08:15:00+03:00",
    "PriceNoTax": 0.13235,
    "PriceWithTax": 0.16610
  },
  {
    "Rank": 81,
    "DateTime": "2025-10-01T08:30:00+03:00",
    "PriceNoTax": 0.13819,
    "PriceWithTax": 0.17343
  },
  {
    "Rank": 78,
    "DateTime": "2025-10-01T08:45:00+03:00",
    "PriceNoTax": 0.13087,
    "PriceWithTax": 0.16424
  },
  {
    "Rank": 82,
    "DateTime": "2025-10-01T09:00:00+03:00",
    "PriceNoTax": 0.14683,
    "PriceWithTax": 0.18427
  },
  {
    "Rank": 73,
    "DateTime": "2025-10-01T09:15:00+03:00",
    "PriceNoTax": 0.10997,
    "PriceWithTax": 0.13801
  },
  {
    "Rank": 70,
    "DateTime": "2025-10-01T09:30:00+03:00",
    "PriceNoTax": 0.10703,
    "PriceWithTax": 0.13432
  },
  {
    "Rank": 59,
    "DateTime": "2025-10-01T09:45:00+03:00",
    "PriceNoTax": 0.09951,
    "PriceWithTax": 0.12489
  },
  {
    "Rank": 76,
    "DateTime": "2025-10-01T10:00:00+03:00",
    "PriceNoTax": 0.11981,
    "PriceWithTax": 0.15036
  },
  {
    "Rank": 72,
    "DateTime": "2025-10-01T10:15:00+03:00",
    "PriceNoTax": 0.1098,
    "PriceWithTax": 0.13780
  },
  {
    "Rank": 58,
    "DateTime": "2025-10-01T10:30:00+03:00",
    "PriceNoTax": 0.09778,
    "PriceWithTax": 0.12271
  },
  {
    "Rank": 47,
    "DateTime": "2025-10-01T10:45:00+03:00",
    "PriceNoTax": 0.08621,
    "PriceWithTax": 0.10819
  },
  {
    "Rank": 68,
    "DateTime": "2025-10-01T11:00:00+03:00",
    "PriceNoTax": 0.10646,
    "PriceWithTax": 0.13361
  },
  {
    "Rank": 57,
    "DateTime": "2025-10-01T11:15:00+03:00",
    "PriceNoTax": 0.09705,
    "PriceWithTax": 0.12180
  },
  {
    "Rank": 44,
    "DateTime": "2025-10-01T11:30:00+03:00",
    "PriceNoTax": 0.08337,
    "PriceWithTax": 0.10463
  },
  {
    "Rank": 31,
    "DateTime": "2025-10-01T11:45:00+03:00",
    "PriceNoTax": 0.06705,
    "PriceWithTax": 0.08415
  },
  {
    "Rank": 60,
    "DateTime": "2025-10-01T12:00:00+03:00",
    "PriceNoTax": 0.09984,
    "PriceWithTax": 0.12530
  },
  {
    "Rank": 50,
    "DateTime": "2025-10-01T12:15:00+03:00",
    "PriceNoTax": 0.08982,
    "PriceWithTax": 0.11272
  },
  {
    "Rank": 42,
    "DateTime": "2025-10-01T12:30:00+03:00",
    "PriceNoTax": 0.07997,
    "PriceWithTax": 0.10036
  },
  {
    "Rank": 40,
    "DateTime": "2025-10-01T12:45:00+03:00",
    "PriceNoTax": 0.07849,
    "PriceWithTax": 0.09850
  },
  {
    "Rank": 67,
    "DateTime": "2025-10-01T13:00:00+03:00",
    "PriceNoTax": 0.10549,
    "PriceWithTax": 0.13239
  },
  {
    "Rank": 65,
    "DateTime": "2025-10-01T13:15:00+03:00",
    "PriceNoTax": 0.10062,
    "PriceWithTax": 0.12628
  },
  {
    "Rank": 64,
    "DateTime": "2025-10-01T13:30:00+03:00",
    "PriceNoTax": 0.09999,
    "PriceWithTax": 0.12549
  },
  {
    "Rank": 63,
    "DateTime": "2025-10-01T13:45:00+03:00",
    "PriceNoTax": 0.09997,
    "PriceWithTax": 0.12546
  },
  {
    "Rank": 46,
    "DateTime": "2025-10-01T14:00:00+03:00",
    "PriceNoTax": 0.08568,
    "PriceWithTax": 0.10753
  },
  {
    "Rank": 53,
    "DateTime": "2025-10-01T14:15:00+03:00",
    "PriceNoTax": 0.09269,
    "PriceWithTax": 0.11633
  },
  {
    "Rank": 61,
    "DateTime": "2025-10-01T14:30:00+03:00",
    "PriceNoTax": 0.09987,
    "PriceWithTax": 0.12534
  },
  {
    "Rank": 77,
    "DateTime": "2025-10-01T14:45:00+03:00",
    "PriceNoTax": 0.12224,
    "PriceWithTax": 0.15341
  },
  {
    "Rank": 37,
    "DateTime": "2025-10-01T15:00:00+03:00",
    "PriceNoTax": 0.07331,
    "PriceWithTax": 0.09200
  },
  {
    "Rank": 41,
    "DateTime": "2025-10-01T15:15:00+03:00",
    "PriceNoTax": 0.07862,
    "PriceWithTax": 0.09867
  },
  {
    "Rank": 49,
    "DateTime": "2025-10-01T15:30:00+03:00",
    "PriceNoTax": 0.08902,
    "PriceWithTax": 0.11172
  },
  {
    "Rank": 74,
    "DateTime": "2025-10-01T15:45:00+03:00",
    "PriceNoTax": 0.11123,
    "PriceWithTax": 0.13959
  },
  {
    "Rank": 39,
    "DateTime": "2025-10-01T16:00:00+03:00",
    "PriceNoTax": 0.07761,
    "PriceWithTax": 0.09740
  },
  {
    "Rank": 45,
    "DateTime": "2025-10-01T16:15:00+03:00",
    "PriceNoTax": 0.08389,
    "PriceWithTax": 0.10528
  },
  {
    "Rank": 56,
    "DateTime": "2025-10-01T16:30:00+03:00",
    "PriceNoTax": 0.09589,
    "PriceWithTax": 0.12034
  },
  {
    "Rank": 89,
    "DateTime": "2025-10-01T16:45:00+03:00",
    "PriceNoTax": 0.18977,
    "PriceWithTax": 0.23816
  },
  {
    "Rank": 55,
    "DateTime": "2025-10-01T17:00:00+03:00",
    "PriceNoTax": 0.09357,
    "PriceWithTax": 0.11743
  },
  {
    "Rank": 62,
    "DateTime": "2025-10-01T17:15:00+03:00",
    "PriceNoTax": 0.0999,
    "PriceWithTax": 0.12537
  },
  {
    "Rank": 86,
    "DateTime": "2025-10-01T17:30:00+03:00",
    "PriceNoTax": 0.15755,
    "PriceWithTax": 0.19773
  },
  {
    "Rank": 90,
    "DateTime": "2025-10-01T17:45:00+03:00",
    "PriceNoTax": 0.19676,
    "PriceWithTax": 0.24693
  },
  {
    "Rank": 66,
    "DateTime": "2025-10-01T18:00:00+03:00",
    "PriceNoTax": 0.10153,
    "PriceWithTax": 0.12742
  },
  {
    "Rank": 80,
    "DateTime": "2025-10-01T18:15:00+03:00",
    "PriceNoTax": 0.13639,
    "PriceWithTax": 0.17117
  },
  {
    "Rank": 85,
    "DateTime": "2025-10-01T18:30:00+03:00",
    "PriceNoTax": 0.15271,
    "PriceWithTax": 0.19165
  },
  {
    "Rank": 92,
    "DateTime": "2025-10-01T18:45:00+03:00",
    "PriceNoTax": 0.20566,
    "PriceWithTax": 0.25810
  },
  {
    "Rank": 84,
    "DateTime": "2025-10-01T19:00:00+03:00",
    "PriceNoTax": 0.15242,
    "PriceWithTax": 0.19129
  },
  {
    "Rank": 87,
    "DateTime": "2025-10-01T19:15:00+03:00",
    "PriceNoTax": 0.161,
    "PriceWithTax": 0.20206
  },
  {
    "Rank": 91,
    "DateTime": "2025-10-01T19:30:00+03:00",
    "PriceNoTax": 0.19867,
    "PriceWithTax": 0.24933
  },
  {
    "Rank": 95,
    "DateTime": "2025-10-01T19:45:00+03:00",
    "PriceNoTax": 0.26338,
    "PriceWithTax": 0.33054
  },
  {
    "Rank": 96,
    "DateTime": "2025-10-01T20:00:00+03:00",
    "PriceNoTax": 0.29125,
    "PriceWithTax": 0.36552
  },
  {
    "Rank": 94,
    "DateTime": "2025-10-01T20:15:00+03:00",
    "PriceNoTax": 0.26106,
    "PriceWithTax": 0.32763
  },
  {
    "Rank": 93,
    "DateTime": "2025-10-01T20:30:00+03:00",
    "PriceNoTax": 0.2236,
    "PriceWithTax": 0.28062
  },
  {
    "Rank": 88,
    "DateTime": "2025-10-01T20:45:00+03:00",
    "PriceNoTax": 0.16899,
    "PriceWithTax": 0.21208
  },
  {
    "Rank": 83,
    "DateTime": "2025-10-01T21:00:00+03:00",
    "PriceNoTax": 0.15182,
    "PriceWithTax": 0.19053
  },
  {
    "Rank": 71,
    "DateTime": "2025-10-01T21:15:00+03:00",
    "PriceNoTax": 0.10857,
    "PriceWithTax": 0.13626
  },
  {
    "Rank": 51,
    "DateTime": "2025-10-01T21:30:00+03:00",
    "PriceNoTax": 0.09046,
    "PriceWithTax": 0.11353
  },
  {
    "Rank": 35,
    "DateTime": "2025-10-01T21:45:00+03:00",
    "PriceNoTax": 0.07149,
    "PriceWithTax": 0.08972
  },
  {
    "Rank": 52,
    "DateTime": "2025-10-01T22:00:00+03:00",
    "PriceNoTax": 0.09262,
    "PriceWithTax": 0.11624
  },
  {
    "Rank": 48,
    "DateTime": "2025-10-01T22:15:00+03:00",
    "PriceNoTax": 0.08639,
    "PriceWithTax": 0.10842
  },
  {
    "Rank": 36,
    "DateTime": "2025-10-01T22:30:00+03:00",
    "PriceNoTax": 0.0722,
    "PriceWithTax": 0.09061
  },
  {
    "Rank": 32,
    "DateTime": "2025-10-01T22:45:00+03:00",
    "PriceNoTax": 0.0685,
    "PriceWithTax": 0.08597
  },
  {
    "Rank": 38,
    "DateTime": "2025-10-01T23:00:00+03:00",
    "PriceNoTax": 0.07533,
    "PriceWithTax": 0.09454
  },
  {
    "Rank": 34,
    "DateTime": "2025-10-01T23:15:00+03:00",
    "PriceNoTax": 0.07006,
    "PriceWithTax": 0.08793
  },
  {
    "Rank": 30,
    "DateTime": "2025-10-01T23:30:00+03:00",
    "PriceNoTax": 0.06548,
    "PriceWithTax": 0.08218
  },
  {
    "Rank": 29,
    "DateTime": "2025-10-01T23:45:00+03:00",
    "PriceNoTax": 0.06158,
    "PriceWithTax": 0.07728
  }
  ])raw";