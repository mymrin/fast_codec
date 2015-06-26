#include "templates_encoders.h"

void Encode(fast_codec::Encoder& encoder, const DefaultIncrementalRefreshMessage& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   if (!msg.MDEntriesSeq.empty())
      encode_u64(encoder, msg.MDEntriesSeq.size());
   for(const auto& i0 : msg.MDEntriesSeq)
   {
      fast_codec::encode_u32(encoder, i0.MDUpdateAction);
      fast_codec::encode_string_ascii(encoder, i0.MDEntryType);
      fast_codec::encode_u64_optional(encoder, i0.SecurityID);
      fast_codec::encode_string_ascii_optional(encoder, i0.Symbol);
      fast_codec::encode_string_ascii_optional(encoder, i0.SecurityGroup);
      fast_codec::encode_u32_optional(encoder, i0.ExchangeTradingSessionID);
      fast_codec::encode_u32(encoder, i0.RptSeq);
      fast_codec::encode_u32_optional(encoder, i0.MarketDepth);
      fast_codec::encode_u32_optional(encoder, i0.MDPriceLevel);
      fast_codec::encode_i64_optional(encoder, i0.MDEntryID);
      fast_codec::encode_decimal_optional(encoder, i0.MDEntryPx);
      fast_codec::encode_i64_optional(encoder, i0.MDEntrySize);
      fast_codec::encode_u32_optional(encoder, i0.MDEntryDate);
      fast_codec::encode_u32(encoder, i0.MDEntryTime);
      fast_codec::encode_i32_optional(encoder, i0.NumberOfOrders);
      fast_codec::encode_string_ascii_optional(encoder, i0.MDEntryTradeType);
      fast_codec::encode_i32_optional(encoder, i0.TrdType);
      fast_codec::encode_decimal_optional(encoder, i0.LastPx);
      fast_codec::encode_i32_optional(encoder, i0.MDFlags);
      fast_codec::encode_string_ascii_optional(encoder, i0.Currency);
   }
}

void Encode(fast_codec::Encoder& encoder, const DefaultSnapshotMessage& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_u32(encoder, msg.RptSeq);
   fast_codec::encode_u32(encoder, msg.TotNumReports);
   fast_codec::encode_u32(encoder, msg.LastMsgSeqNumProcessed);
   fast_codec::encode_u64_optional(encoder, msg.SecurityID);
   fast_codec::encode_string_ascii_optional(encoder, msg.Symbol);
   fast_codec::encode_string_ascii_optional(encoder, msg.SecurityGroup);
   if (!msg.MDEntriesSeq.empty())
      encode_u64(encoder, msg.MDEntriesSeq.size());
   for(const auto& i0 : msg.MDEntriesSeq)
   {
      fast_codec::encode_string_ascii(encoder, i0.MDEntryType);
      fast_codec::encode_u32_optional(encoder, i0.ExchangeTradingSessionID);
      fast_codec::encode_i64_optional(encoder, i0.MDEntryID);
      fast_codec::encode_u32_optional(encoder, i0.MarketDepth);
      fast_codec::encode_decimal_optional(encoder, i0.MDEntryPx);
      fast_codec::encode_u32_optional(encoder, i0.MDEntryDate);
      fast_codec::encode_u32(encoder, i0.MDEntryTime);
      fast_codec::encode_i64_optional(encoder, i0.MDEntrySize);
      fast_codec::encode_u32_optional(encoder, i0.MDPriceLevel);
      fast_codec::encode_i32_optional(encoder, i0.NumberOfOrders);
      fast_codec::encode_string_ascii_optional(encoder, i0.MDEntryTradeType);
      fast_codec::encode_i32_optional(encoder, i0.TrdType);
      fast_codec::encode_i32_optional(encoder, i0.MDFlags);
      fast_codec::encode_string_ascii_optional(encoder, i0.Currency);
   }
}

void Encode(fast_codec::Encoder& encoder, const SecurityDefinition& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_u32(encoder, msg.TotNumReports);
   fast_codec::encode_string_ascii(encoder, msg.Symbol);
   fast_codec::encode_string_utf8_optional(encoder, msg.SecurityDesc);
   fast_codec::encode_u64(encoder, msg.SecurityID);
   fast_codec::encode_string_ascii_optional(encoder, msg.SecurityAltID);
   fast_codec::encode_string_ascii_optional(encoder, msg.SecurityAltIDSource);
   fast_codec::encode_string_ascii_optional(encoder, msg.SecurityType);
   fast_codec::encode_string_ascii_optional(encoder, msg.CFICode);
   fast_codec::encode_decimal_optional(encoder, msg.StrikePrice);
   fast_codec::encode_decimal_optional(encoder, msg.ContractMultiplier);
   fast_codec::encode_u32_optional(encoder, msg.SecurityTradingStatus);
   fast_codec::encode_string_ascii_optional(encoder, msg.Currency);
   fast_codec::encode_string_ascii(encoder, msg.MarketSegmentID);
   fast_codec::encode_u32_optional(encoder, msg.TradingSessionID);
   fast_codec::encode_u32_optional(encoder, msg.ExchangeTradingSessionID);
   fast_codec::encode_decimal_optional(encoder, msg.Volatility);
   if (!msg.MDFeedTypesSeq.empty())
      encode_u64(encoder, msg.MDFeedTypesSeq.size());
   for(const auto& i0 : msg.MDFeedTypesSeq)
   {
      fast_codec::encode_string_ascii(encoder, i0.MDFeedType);
      fast_codec::encode_u32_optional(encoder, i0.MarketDepth);
      fast_codec::encode_u32_optional(encoder, i0.MDBookType);
   }
   if (!msg.UnderlyingsSeq.empty())
      encode_u64(encoder, msg.UnderlyingsSeq.size());
   for(const auto& i0 : msg.UnderlyingsSeq)
   {
      fast_codec::encode_string_ascii(encoder, i0.UnderlyingSymbol);
      fast_codec::encode_u64_optional(encoder, i0.UnderlyingSecurityID);
   }
   fast_codec::encode_decimal_optional(encoder, msg.HighLimitPx);
   fast_codec::encode_decimal_optional(encoder, msg.LowLimitPx);
   fast_codec::encode_decimal_optional(encoder, msg.MinPriceIncrement);
   fast_codec::encode_decimal_optional(encoder, msg.MinPriceIncrementAmount);
   fast_codec::encode_decimal_optional(encoder, msg.InitialMarginOnBuy);
   fast_codec::encode_decimal_optional(encoder, msg.InitialMarginOnSell);
   fast_codec::encode_decimal_optional(encoder, msg.InitialMarginSyntetic);
   fast_codec::encode_string_ascii_optional(encoder, msg.QuotationList);
   fast_codec::encode_decimal_optional(encoder, msg.TheorPrice);
   fast_codec::encode_decimal_optional(encoder, msg.TheorPriceLimit);
   if (!msg.InstrumentLegsSeq.empty())
      encode_u64(encoder, msg.InstrumentLegsSeq.size());
   for(const auto& i0 : msg.InstrumentLegsSeq)
   {
      fast_codec::encode_string_ascii(encoder, i0.LegSymbol);
      fast_codec::encode_u64(encoder, i0.LegSecurityID);
      fast_codec::encode_decimal(encoder, i0.LegRatioQty);
   }
   if (!msg.InstrumentAttributesSeq.empty())
      encode_u64(encoder, msg.InstrumentAttributesSeq.size());
   for(const auto& i0 : msg.InstrumentAttributesSeq)
   {
      fast_codec::encode_i32(encoder, i0.InstrAttribType);
      fast_codec::encode_string_ascii(encoder, i0.InstrAttribValue);
   }
   fast_codec::encode_decimal_optional(encoder, msg.UnderlyingQty);
   fast_codec::encode_string_ascii_optional(encoder, msg.UnderlyingCurrency);
   if (!msg.EvntGrpSeq.empty())
      encode_u64(encoder, msg.EvntGrpSeq.size());
   for(const auto& i0 : msg.EvntGrpSeq)
   {
      fast_codec::encode_i32(encoder, i0.EventType);
      fast_codec::encode_u32(encoder, i0.EventDate);
      fast_codec::encode_u64(encoder, i0.EventTime);
   }
   fast_codec::encode_u32_optional(encoder, msg.MaturityDate);
   fast_codec::encode_u32_optional(encoder, msg.MaturityTime);
}

void Encode(fast_codec::Encoder& encoder, const SecurityDefinitionUpdateReport& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_u64(encoder, msg.SecurityID);
   fast_codec::encode_decimal_optional(encoder, msg.Volatility);
   fast_codec::encode_decimal_optional(encoder, msg.TheorPrice);
   fast_codec::encode_decimal_optional(encoder, msg.TheorPriceLimit);
}

void Encode(fast_codec::Encoder& encoder, const SecurityStatus& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_u64(encoder, msg.SecurityID);
   fast_codec::encode_string_ascii(encoder, msg.Symbol);
   fast_codec::encode_u32_optional(encoder, msg.SecurityTradingStatus);
   fast_codec::encode_decimal_optional(encoder, msg.HighLimitPx);
   fast_codec::encode_decimal_optional(encoder, msg.LowLimitPx);
   fast_codec::encode_decimal_optional(encoder, msg.InitialMarginOnBuy);
   fast_codec::encode_decimal_optional(encoder, msg.InitialMarginOnSell);
   fast_codec::encode_decimal_optional(encoder, msg.InitialMarginSyntetic);
}

void Encode(fast_codec::Encoder& encoder, const Heartbeat& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
}

void Encode(fast_codec::Encoder& encoder, const SequenceReset& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_u32(encoder, msg.NewSeqNo);
}

void Encode(fast_codec::Encoder& encoder, const TradingSessionStatus& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_u64(encoder, msg.TradSesOpenTime);
   fast_codec::encode_u64(encoder, msg.TradSesCloseTime);
   fast_codec::encode_u64_optional(encoder, msg.TradSesIntermClearingStartTime);
   fast_codec::encode_u64_optional(encoder, msg.TradSesIntermClearingEndTime);
   fast_codec::encode_u32(encoder, msg.TradingSessionID);
   fast_codec::encode_u32_optional(encoder, msg.ExchangeTradingSessionID);
   fast_codec::encode_u32(encoder, msg.TradSesStatus);
   fast_codec::encode_string_ascii(encoder, msg.MarketSegmentID);
   fast_codec::encode_i32_optional(encoder, msg.TradSesEvent);
}

void Encode(fast_codec::Encoder& encoder, const News& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_string_ascii_optional(encoder, msg.NewsId);
   fast_codec::encode_u64_optional(encoder, msg.OrigTime);
   fast_codec::encode_string_ascii_optional(encoder, msg.LanguageCode);
   fast_codec::encode_u32_optional(encoder, msg.Urgency);
   fast_codec::encode_string_utf8(encoder, msg.Headline);
   fast_codec::encode_string_ascii_optional(encoder, msg.MarketSegmentID);
   if (!msg.NewsTextSeq.empty())
      encode_u64(encoder, msg.NewsTextSeq.size());
   for(const auto& i0 : msg.NewsTextSeq)
   {
      fast_codec::encode_string_utf8(encoder, i0.Text);
   }
}

void Encode(fast_codec::Encoder& encoder, const Logon& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
}

void Encode(fast_codec::Encoder& encoder, const Logout& msg)
{
   // Preamble encoding
   fast_codec::write(encoder, msg.MsgSeqNum);

   // Constant PMAP encoding
   // 0xC0 is binary '1100 0000', the firts '1' is stop bit, the second '1' is a bit of template id
   fast_codec::write_byte(encoder, 0xC0);

   // Template id encoding
   fast_codec::encode_u32(encoder, msg.id);

   fast_codec::encode_u32(encoder, msg.MsgSeqNum);
   fast_codec::encode_u64(encoder, msg.SendingTime);
   fast_codec::encode_string_ascii_optional(encoder, msg.Text);
}

