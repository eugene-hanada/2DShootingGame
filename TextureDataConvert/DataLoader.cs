using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Text.RegularExpressions;

namespace TextureDataConvert
{
	internal class DataLoader
	{
		private string fileName_;
		private Dictionary<string,List<TextureData>> textureData_;

		DataLoader(string fileName)
		{
			Load(fileName);
		}

		bool Load(string fnameName)
		{
			XElement xml;
			try
			{
				xml = XElement.Load(fnameName);
			}
			catch (Exception ex)
			{
				Console.WriteLine(ex.Message);
				return false;
			}

			var img = xml.Attribute("imagePath");
			if (img == null)
			{
				return false;
			}

			fileName_ = img.Value;

			foreach (var sp in xml.Elements())
			{
				var nameAtr = sp.Attribute("n");
				if (nameAtr != null)
				{
					var name = nameAtr.Value;
					
				}
				
			
			}

			return true;
		}

		
		private class TextureData
		{
			private Vector2 pos_;
			private Vector2 wh_;

			public TextureData(ref XElement sprite)
			{
				var x = sprite.Attribute("x");
				var y = sprite.Attribute("y");
				if (x == null || y == null)
				{
					return;
				}
				pos_ = new Vector2(Int32.Parse(x.Value), Int32.Parse(y.Value));

				var w = sprite.Attribute("w");
				var h = sprite.Attribute("h");

				if (w == null || h == null)
				{
					return;
				}
				wh_ = new Vector2(Int32.Parse(w.Value), Int32.Parse(h.Value));

			}

		}
		
	}
}
