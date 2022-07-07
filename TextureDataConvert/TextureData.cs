using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace TextureDataConvert
{
	internal class TextureData
	{
		private Vector2 pos_;
		private Vector2 wh_;

		public TextureData(XElement? sprite)
		{
			if (sprite == null)
			{
				throw new ArgumentNullException(nameof(sprite));
			}

			var x = sprite.Attribute("x");
			var y = sprite.Attribute("y");
			if (x == null || y == null)
			{
				throw new ArgumentNullException("xもしくはyの値がありません");
			}
			pos_ = new Vector2(float.Parse(x.Value), float.Parse(y.Value));

			var w = sprite.Attribute("w");
			var h = sprite.Attribute("h");

			if (w == null || h == null)
			{
				throw new ArgumentNullException("wもしくはhの値がありません");
			}
			wh_ = new Vector2(float.Parse(w.Value), float.Parse(h.Value));

		}

		public void Write(BinaryWriter bw)
		{
			pos_.Write(bw);
			wh_.Write(bw);
		}

	}
}
